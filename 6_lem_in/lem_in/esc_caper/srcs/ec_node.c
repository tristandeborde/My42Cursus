/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:36:23 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 17:44:57 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

void	ec_node_upz_by_id(int id, t_list *list)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		if (node->id == id)
		{
			node->z = node->z + 2;
		}
		list = list->next;
	}
}

char	*ec_name_by_node(t_list *elem)
{
	t_node	*node;
	char	*name;

	node = elem->content;
	name = node->label;
	return (name);
}

int		ec_node_id_by_name(t_cnf cnf, char *name)
{
	t_list	*elem;
	t_node	*node;

	elem = cnf.node;
	while (elem)
	{
		if (ft_strcmp(ec_name_by_node(elem), name) == 0)
		{
			node = elem->content;
			return (node->id);
		}
		elem = elem->next;
	}
	return (0);
}
