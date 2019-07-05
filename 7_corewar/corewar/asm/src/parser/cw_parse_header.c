/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 12:11:09 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/02 12:44:28 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "asm_err.h"

extern int		cw_strextend(char **str, char *tmp)
{
	char	*cpy;
	int		len;

	if (*str == NULL)
	{
		*str = ft_strdup(tmp);
		return (1);
	}
	len = ft_strlen(*str);
	if (!(cpy = ft_memalloc(sizeof(char) * len + 1)))
		return (0);
	ft_memcpy((void *)cpy, (void *)*str, sizeof(char) * (len + 1));
	ft_memdel((void **)str);
	*str = ft_strjoin(cpy, tmp);
	ft_memdel((void **)&cpy);
	return (1);
}

static char		ft_getstr_head(char *line, char **buff, int add)
{
	int				start;
	int				end;

	start = *buff == 0 ? add : 0;
	if (*buff == 0)
	{
		while (line[start] != '"' && line[start] != '\0' && (line[start] == ' '
				|| line[start] == '\t'))
			start++;
		if (line[start] == '\0' || line[start] != '"')
			return (-1);
	}
	end = (start != 0) ? start + 1 : 0;
	while (line[end] != '"' && line[end] != '\0')
		end++;
	start = (line[start] == '"') ? start + 1 : start;
	if (cw_strextend(buff, &line[start]) == 0)
	{
		if (*buff)
			ft_strdel(buff);
		return (ALLOC_ERR);
	}
	return (cw_end_header(line, end) == 0 ? 0 : 2);
}

static int		cw_parse_header_checkname(char *line, t_header *head, \
		char **buff, int *stat)
{
	int		ret;
	int		i;

	*stat = 1;
	if (*(head->prog_name) != '\0')
		return (PROG_HEADER_ERR1);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	ret = ft_getstr_head(line, buff, i + ft_strlen(NAME_CMD_STRING));
	if (ret > 0)
	{
		cw_00101010_by_max(*buff);
		if (ft_strlen(*buff) > PROG_NAME_LENGTH + 1)
			return (PROG_HEADER_ERR3);
		ft_strcpy(head->prog_name, *buff);
		ft_strdel((char **)buff);
		*stat = 0;
	}
	else if (ret != 0)
		ret = PROG_HEADER_ERR2;
	else
		cw_strextend(buff, "\n");
	return (ret);
}

static int		cw_parse_header_checkcomment(char *line, t_header *head, \
		char **buff, int *stat)
{
	int		ret;
	int		i;

	*stat = 2;
	if (*(head->comment) != '\0')
		return (PROG_HEADER_ERR4);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	ret = ft_getstr_head(line, buff, i + ft_strlen(COMMENT_CMD_STRING));
	if (ret > 0)
	{
		cw_00101010_by_max(*buff);
		if (ft_strlen(*buff) > COMMENT_LENGTH + 1)
			return (PROG_HEADER_ERR5);
		ft_strcpy(head->comment, *buff);
		ft_strdel((char **)buff);
		*stat = 0;
	}
	else if (ret != 0)
		ret = PROG_HEADER_ERR7;
	else
		cw_strextend(buff, "\n");
	return (ret);
}

extern int		cw_parse_header(char *line, t_header *head)
{
	static char	*buff = 0;
	static int	stat = 0;
	int			ret;
	int			i;

	ret = 1;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (*(line + i) == '\0' && buff == NULL)
		return (1);
	if ((ft_strncmp(NAME_CMD_STRING, line + i, \
				ft_strlen(NAME_CMD_STRING)) == 0 && buff == NULL) || stat == 1)
		ret = cw_parse_header_checkname(line, head, &buff, &stat);
	else if ((ft_strncmp(COMMENT_CMD_STRING, line + i, \
		ft_strlen(COMMENT_CMD_STRING)) == 0 && buff == NULL) || stat == 2)
		ret = cw_parse_header_checkcomment(line, head, &buff, &stat);
	if (ret == 1 && (*(head->comment) == '\0' || *(head->prog_name) == '\0'))
		ret = PROG_HEADER_ERR6;
	return (ret);
}
