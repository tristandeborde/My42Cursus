/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_images_maping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:46:22 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/26 18:53:35 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

int		dm_cn(t_node *node, int id)
{
	if (node->id == id)
		return (0xff0000);
	if (node->status == 1)
		return (0x00ff00);
	if (node->status == 2)
		return (0x0000ff);
	return (0xffffff);
}

t_mlx	dm_draw_nodes(t_mlx mlx)
{
	t_list	*list;
	t_node	*node;
	int		i;
	int		x;
	int		y;

	i = (1000 - (1000 / mlx.cnf.grid_size) * mlx.cnf.grid_size) / 2;
	list = mlx.cnf.node;
	while (list)
	{
		node = list->content;
		x = node->x * (1000 / mlx.cnf.grid_size) + i + mlx.cnf.ox;
		y = node->y * (1000 / mlx.cnf.grid_size) + i + mlx.cnf.oy;
		if (x > 0 && x < 1000 && y > 0 && y < 1000)
		{
			mlx.img = circle(mlx.img, stp(x, y), (1000 / \
					mlx.cnf.grid_size) / 3, dm_cn(node, mlx.cnf.id));
		}
		list = list->next;
	}
	return (mlx);
}

t_pos	dm_pnid(t_mlx mlx, t_list *list, int id, int size)
{
	t_node	*node;
	int		x;
	int		y;
	int		i;

	i = (1000 - (1000 / size) * size) / 2;
	while (list)
	{
		node = list->content;
		if (node->id == id)
		{
			x = node->x * (1000 / size) + i + mlx.cnf.ox;
			y = node->y * (1000 / size) + i + mlx.cnf.oy;
			return (stp(x, y));
		}
		list = list->next;
	}
	return (stp(0, 0));
}

t_img	dm_line(t_img img, t_pos p1, t_pos p2, int color)
{
	if (p1.x < 1000 && p1.x > 0 && p2.x > 0 && p2.x < 1000
			&& p1.y > 0 && p1.y < 1000 && p2.y > 0 && p2.y < 1000)
		img = line(img, p1, p2, color);
	return (img);
}

t_mlx	dm_draw_tnls(t_mlx mlx)
{
	t_list	*list;
	t_tnl	*tnl;
	t_list	*nodes;
	int		size;

	size = mlx.cnf.grid_size;
	nodes = mlx.cnf.node;
	list = mlx.cnf.tnl;
	while (list)
	{
		tnl = list->content;
		mlx.img = dm_line(mlx.img, dm_pnid(mlx, nodes, tnl->id1, size),\
				dm_pnid(mlx, nodes, tnl->id2, size), 0xffffff);
		list = list->next;
	}
	return (mlx);
}
