/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_tube_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:29:52 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/03 19:29:54 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

void	ec_destroy_dtube(t_dos **dmap)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		free(dmap[i]);
		i++;
	}
	free(dmap);
}

t_dos	**ec_new_tube_dmap(void)
{
	t_dos	**dmap;
	int		i;

	i = 0;
	dmap = (t_dos**)malloc(sizeof(t_dos*) * 4);
	while (i < 4)
	{
		dmap[i] = (t_dos*)malloc(sizeof(t_dos) * 12);
		i++;
	}
	return (dmap);
}

void	ec_destroy_ptube(t_pos **pmap)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		free(pmap[i]);
		i++;
	}
	free(pmap);
}

t_pos	**ec_new_tube_pmap(void)
{
	t_pos	**pmap;
	int		i;

	i = 0;
	pmap = (t_pos **)malloc(sizeof(t_pos *) * 4);
	while (i < 4)
	{
		pmap[i] = (t_pos *)malloc(sizeof(t_pos) * 12);
		i++;
	}
	return (pmap);
}
