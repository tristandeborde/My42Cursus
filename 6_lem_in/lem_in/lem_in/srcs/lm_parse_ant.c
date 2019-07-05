/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_ant.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:32:14 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/02 18:41:40 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_data	lm_fetch_ant(t_data data, int *status, char **line)
{
	*status = 0;
	if (ft_strisdig(*line))
		data.nb_ants = ft_atoi(*line);
	else
		data = lm_fetch_node(data, status, line);
	return (data);
}

t_data	lm_parse_ants(t_data data, int *status, char **line)
{
	if (ft_gnl(0, line) > 0 && *line)
	{
		if (lm_line_is_com(*line))
			return (data);
		data = lm_fetch_ant(data, status, line);
	}
	else
		*status = 3;
	return (data);
}
