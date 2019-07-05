/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:36:10 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/13 11:26:15 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_data	lm_fetch_data(t_data data)
{
	int		status;
	t_parse	*parse;
	char	*line;

	status = 0;
	parse = lm_getparse();
	line = NULL;
	while (status < 3)
	{
		data = parse[status].f(data, &status, &line);
		if (line)
		{
			if (status != 3)
			{
				line = ft_realloc(line, "\n");
				data.cmd = ft_realloc(data.cmd, line);
			}
			free(line);
			line = NULL;
		}
	}
	return (data);
}
