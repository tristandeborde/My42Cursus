/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_label.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:38:16 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/16 17:32:52 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_err.h"

static char		**cw_strsplit_first(const char *str, char c)
{
	char		*mark;
	size_t		len1;
	size_t		len2;
	char		**split;

	if (c == '\0' || str == 0)
		return (0);
	mark = ft_strchr(str, c);
	if (*mark != c)
	{
		return (0);
	}
	if (!(split = (char **)ft_memalloc(sizeof(char *) * (2 + 1))))
		return (0);
	len1 = ft_strlen(mark);
	len2 = ft_strlen(str) - len1;
	split[1] = ft_strdup(++mark);
	split[0] = ft_strdup(str);
	split[0][len2] = '\0';
	split[2] = 0;
	return (split);
}

static char		*cw_carchr(char *line, char *c)
{
	int			i;
	int			j;

	i = 0;
	while (line[i] != '\0')
	{
		j = 0;
		while (c[j] != '\0')
		{
			if (line[i] == c[j])
				return (&c[j]);
			j++;
		}
		i++;
	}
	return (&line[i]);
}

static int		cw_check_label(char *label)
{
	int			i;

	i = 0;
	while (label[i] != '\0')
	{
		if (!ft_isalnum(label[i]))
		{
			if (label[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

extern int		cw_parse_label(char *line, t_instruct **inst, char ***lab)
{
	char		*end_label;

	end_label = cw_carchr(line, ", \t:");
	if (*end_label == ':')
	{
		if (end_label == line)
			return (PROG_LABEL_ERR1);
		if (!(*lab = cw_strsplit_first(line, ':')))
			return (ALLOC_ERR);
		if (ft_strlen((*lab)[0]) == 0)
			return (PROG_LABEL_ERR1);
		if (!cw_check_label((*lab)[0]))
			return (PROG_LABEL_ERR2);
		if (!((*inst)->label = ft_strdup((*lab)[0])))
			return (ALLOC_ERR);
		return (1);
	}
	return (0);
}
