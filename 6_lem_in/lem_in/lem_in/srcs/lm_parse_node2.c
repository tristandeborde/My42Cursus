/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_node2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:39:34 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/20 12:50:20 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lm_line_is_status(char *line)
{
	if (line[0] == '#' && ft_strlen(line) > 3 && line[1] == '#')
	{
		if (ft_strcmp(line, "##end") == 0)
			return (2);
		if (ft_strcmp(line, "##start") == 0)
			return (1);
		return (-1);
	}
	return (0);
}
