/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:48:06 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/06 09:37:34 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lm_line_is_com(char *line)
{
	if (line[0] == '#' && ft_strlen(line) > 1 && line[1] != '#')
		return (1);
	return (0);
}

int		ft_strtabsize(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

int		ft_strisdig(char *str)
{
	int			i;
	intmax_t	conv;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	conv = ft_atoi_base_max(str, 10);
	if (i > 11 || conv > INT_MAX || conv < INT_MIN)
		return (0);
	if (str[i] == '\0' && i != 0)
		return (1);
	return (0);
}

void	lm_destroy_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_parse	*lm_getparse(void)
{
	static t_parse	new[3] = {
		{&lm_parse_ants},
		{&lm_parse_nodes},
		{&lm_parse_links}
	};

	return (new);
}
