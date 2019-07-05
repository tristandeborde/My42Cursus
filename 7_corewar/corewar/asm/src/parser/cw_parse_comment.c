/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 11:50:21 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/01 18:19:19 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

void			cw_00101010_by_max(char *just_for_fun)
{
	int		this_is_a_disgusting_fct;
	int		*i;

	this_is_a_disgusting_fct = 0;
	i = &this_is_a_disgusting_fct;
	*i = ft_strlen(just_for_fun);
	while (i >= 0 && (just_for_fun[*i] == '\0' || just_for_fun[*i] == ' '
				|| just_for_fun[*i] == '\t'))
	{
		if (just_for_fun[*i] == 0x22)
			break ;
		*(just_for_fun + *i) = 0b00000000;
		*i = this_is_a_disgusting_fct - 0b1;
	}
}

int				cw_end_header(char *str, int end)
{
	int		i;

	if (str[end] == '\0')
		return (0);
	i = 1;
	while (str[end + i] != '\0')
	{
		if (str[end + i] != ' ' && str[end + i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void			cw_trim_line(char *line)
{
	int		i;

	i = ft_strlen(line);
	while (i >= 0 && (line[i] == '\0' || line[i] == ' ' || line[i] == '\t'))
	{
		*(line + i) = '\0';
		i--;
	}
}

extern void		cw_parse_comment(char *line)
{
	char		*tmp;

	if (*line != '\0')
	{
		if (*line == COMMENT_CHAR)
			*line = '\0';
		else
		{
			tmp = ft_strchr(line, COMMENT_CHAR);
			if (tmp != 0)
				*tmp = '\0';
		}
	}
}
