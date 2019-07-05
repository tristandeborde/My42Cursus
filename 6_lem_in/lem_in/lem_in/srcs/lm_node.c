/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:36:23 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 18:08:08 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*lm_name_by_node(t_list *elem)
{
	t_node	*node;
	char	*name;

	node = elem->content;
	name = node->id;
	return (name);
}

t_list	*lm_node_by_name(t_data data, char *name)
{
	t_list	*elem;

	elem = data.node;
	while (elem)
	{
		if (ft_strcmp(lm_name_by_node(elem), name) == 0)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}
