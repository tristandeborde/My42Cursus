/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:42:22 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/27 12:27:49 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

int		dm_node_fresh_id(t_list *list)
{
	t_node	*node;

	if (list)
	{
		while (list->next)
			list = list->next;
		node = list->content;
		return (node->id + 1);
	}
	return (1);
}

int		dm_check_node_pos(t_list *list, int x, int y)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		if (x == node->x && y == node->y)
			return (0);
		list = list->next;
	}
	return (1);
}

t_list	*cnf_remove_status(t_mlx *mlx, t_list *list, int status)
{
	t_list	*elem;
	t_node	*node;
	t_btn	*btn;

	elem = list;
	while (elem)
	{
		node = elem->content;
		if (node->status == status)
			node->status = 0;
		elem = elem->next;
	}
	elem = mlx->cnf.btn;
	while (elem)
	{
		btn = elem->content;
		if (btn->id == 10 || btn->id == 11)
			btn->status = 0;
		elem = elem->next;
	}
	return (list);
}

t_list	*cnf_add_node(t_mlx mlx, t_list *list, int x, int y)
{
	t_node	node;
	int		ox;
	int		oy;
	int		id;

	ox = dm_node_oxy(mlx, x, mlx.cnf.ox);
	oy = dm_node_oxy(mlx, y, mlx.cnf.oy);
	id = cnf_node_id_by_pos(list, ox, oy);
	if (dm_check_node_pos(list, ox, oy) == 1)
	{
		node.id = dm_node_fresh_id(list);
		node.x = ox;
		node.y = oy;
		node.z = 0;
		node.status = mlx.cnf.status;
		if (node.status != 0)
			list = cnf_remove_status(&mlx, list, node.status);
		ft_lstaddend(&(list), ft_lstnew(&node, sizeof(t_node)));
	}
	else
		list = dm_free_node_id(list, id);
	return (list);
}

int		cnf_node_id_by_pos(t_list *list, int x, int y)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		if (x == node->x && y == node->y)
			return (node->id);
		list = list->next;
	}
	return (0);
}
