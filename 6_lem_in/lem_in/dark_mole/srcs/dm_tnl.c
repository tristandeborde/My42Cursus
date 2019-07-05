/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_tnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:42:14 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/27 13:01:18 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

int		dm_check_tnl_ids(t_list *list, int id1, int id2)
{
	t_tnl	*tnl;

	while (list)
	{
		tnl = list->content;
		if ((tnl->id1 == id1 && tnl->id2 == id2)
				|| (tnl->id1 == id2 && tnl->id2 == id1))
			return (0);
		list = list->next;
	}
	return (1);
}

t_list	*dm_free_tnl_ids(t_list *elem, int id1, int id2)
{
	t_list	*list;
	t_list	*buff;
	t_list	*prev;
	t_tnl	*tnl;

	list = elem;
	prev = list;
	while (list)
	{
		tnl = list->content;
		if ((tnl->id1 == id1 && tnl->id2 == id2)
				|| (tnl->id1 == id2 && tnl->id2 == id1))
		{
			buff = list->next;
			free(tnl);
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

t_list	*cnf_add_tnl(t_list *list, int id1, int id2)
{
	t_tnl	tnl;

	if (dm_check_tnl_ids(list, id1, id2) == 1)
	{
		tnl.id1 = id1;
		tnl.id2 = id2;
		ft_lstaddend(&(list), ft_lstnew(&tnl, sizeof(t_tnl)));
	}
	else
		list = dm_free_tnl_ids(list, id1, id2);
	return (list);
}

t_cnf	cnf_add_link(t_mlx mlx, t_cnf cnf, int x, int y)
{
	int		ox;
	int		oy;
	int		id;

	ox = dm_node_oxy(mlx, x, cnf.ox);
	oy = dm_node_oxy(mlx, y, cnf.oy);
	if ((id = cnf_node_id_by_pos(cnf.node, ox, oy)) != 0)
	{
		if (cnf.id != 0 && cnf.id != id)
		{
			cnf.tnl = cnf_add_tnl(cnf.tnl, cnf.id, id);
			cnf.id = 0;
		}
		else
			cnf.id = id;
	}
	else
		cnf.id = 0;
	return (cnf);
}
