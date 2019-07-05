/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:48:06 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/02 15:42:06 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

int		ec_line_is_com(char *line)
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
	int		i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == '\0' && i != 0)
		return (1);
	return (0);
}

void	ec_destroy_tab(char **tab)
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

t_parse	*ec_getparse(void)
{
	static t_parse	new[3] = {
		{&ec_parse_ants},
		{&ec_parse_nodes},
		{&ec_parse_links}
	};

	return (new);
}
