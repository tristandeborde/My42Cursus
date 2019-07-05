/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_link_vals_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 18:04:45 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/14 16:08:20 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*lm_start_node(t_list *list)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		if (node->status == 1)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	lm_node_dist(t_list *node, int dist)
{
	t_node	*content;
	t_list	*list;
	t_link	*link;

	if (node && (content = node->content))
	{
		if (content->status != 2
				&& (content->dist == -1 || dist < content->dist))
		{
			content->dist = dist;
			list = content->link;
			while (list)
			{
				if ((link = list->content) != NULL)
				{
					lm_node_dist(link->node, dist + 1);
				}
				list = list->next;
			}
		}
	}
}

void	lm_link_vals_fill(t_data *data)
{
	t_list	*start;

	start = lm_start_node(data->node);
	lm_node_dist(start, 0);
}
