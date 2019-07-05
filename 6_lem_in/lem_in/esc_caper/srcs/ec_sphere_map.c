/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_sphere_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:17:18 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/28 11:17:19 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_pos	**ec_new_pmap(void)
{
	t_pos	**map;
	int		i;

	i = 0;
	map = (t_pos**)malloc(sizeof(t_pos*) * 18);
	while (i < 18)
	{
		map[i] = (t_pos*)malloc(sizeof(t_pos) * 10);
		i++;
	}
	return (map);
}

t_dos	**ec_new_dmap(void)
{
	t_dos	**map;
	int		i;

	i = 0;
	map = (t_dos**)malloc(sizeof(t_dos*) * 18);
	while (i < 18)
	{
		map[i] = (t_dos*)malloc(sizeof(t_dos) * 10);
		i++;
	}
	return (map);
}

void	ec_destroy_pmap(t_pos **map)
{
	int		i;

	i = 0;
	while (i < 18)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ec_destroy_dmap(t_dos **map)
{
	int		i;

	i = 0;
	while (i < 18)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
