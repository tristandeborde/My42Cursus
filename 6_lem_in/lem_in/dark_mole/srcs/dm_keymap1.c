/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_keymap1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:00:00 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/26 18:40:35 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

t_mlx	dm_reset_btn(t_mlx mlx)
{
	t_list	*list;
	t_btn	*btn;

	list = mlx.cnf.btn;
	while (list)
	{
		btn = list->content;
		btn->status = 0;
		list = list->next;
	}
	return (mlx);
}

int		dm_node_oxy(t_mlx mlx, int x, int mod)
{
	int		size;
	int		i;
	int		scale;

	size = mlx.cnf.grid_size;
	scale = 1000 / size;
	i = (1000 - (1000 / size) * size) / 2 - scale / 2;
	return ((x - i - mod) / scale);
}

int		dm_clicked_btn(t_mlx mlx)
{
	t_list	*list;
	t_btn	*btn;

	list = mlx.cnf.btn;
	while (list)
	{
		btn = list->content;
		if (btn->status == 1)
			return (btn->id);
		list = list->next;
	}
	return (0);
}

t_mlx	cnf_add_map(t_mlx mlx, int x, int y)
{
	int		id;

	id = dm_clicked_btn(mlx);
	if (id != 0)
	{
		if (id == 7)
		{
			mlx.cnf.node = cnf_add_node(mlx, mlx.cnf.node, x, y);
			mlx.cnf.status = 0;
		}
		if (id == 8)
			mlx.cnf = cnf_add_link(mlx, mlx.cnf, x, y);
	}
	return (mlx);
}
