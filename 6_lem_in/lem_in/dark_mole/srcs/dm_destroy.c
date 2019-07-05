/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:43:05 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 16:15:05 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

t_cnf	cnf_reset_tnls(t_cnf cnf)
{
	t_list	*list;
	t_list	*buff;

	list = cnf.tnl;
	while (list)
	{
		free(list->content);
		buff = list->next;
		free(list);
		list = buff;
	}
	cnf.tnl = NULL;
	return (cnf);
}

t_cnf	cnf_reset_nodes(t_cnf cnf)
{
	t_list	*list;
	t_list	*buff;

	list = cnf.node;
	while (list)
	{
		free(list->content);
		buff = list->next;
		free(list);
		list = buff;
	}
	cnf.node = NULL;
	return (cnf);
}

t_list	*dm_free_node_id(t_list *elem, int id)
{
	t_list	*list;
	t_list	*buff;
	t_list	*prev;
	t_node	*node;

	list = elem;
	prev = list;
	while (list)
	{
		node = list->content;
		if (node->id == id)
		{
			buff = list->next;
			free(node);
			if (list == elem)
				elem = buff;
			free(list);
			list = prev;
			list->next = buff;
		}
		prev = list;
		list = list->next;
	}
	return (elem);
}

int		dm_node_missing_id(t_list *list, int id)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		if (node->id == id)
			return (0);
		list = list->next;
	}
	return (id);
}

t_mlx	dm_free_bad_tnl(t_mlx mlx)
{
	t_list	*list;
	t_tnl	*tnl;
	int		id;

	list = mlx.cnf.tnl;
	while (list)
	{
		tnl = list->content;
		if ((id = dm_node_missing_id(mlx.cnf.node, tnl->id1)) != 0)
		{
			mlx.cnf.tnl = dm_free_tnl_ids(mlx.cnf.tnl, tnl->id1, tnl->id2);
			list = mlx.cnf.tnl;
		}
		else if ((id = dm_node_missing_id(mlx.cnf.node, tnl->id2)) != 0)
		{
			mlx.cnf.tnl = dm_free_tnl_ids(mlx.cnf.tnl, tnl->id1, tnl->id2);
			list = mlx.cnf.tnl;
		}
		else
			list = list->next;
	}
	return (mlx);
}
