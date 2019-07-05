/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_find_one_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 16:58:17 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/14 14:43:42 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lm_link_val(t_node *node, t_node *curr)
{
	t_link	*link;
	t_list	*list;

	list = node->link;
	while (list)
	{
		link = list->content;
		if (link->node->content == curr)
			return (link->val);
		list = list->next;
	}
	return (0);
}

t_node	*lm_lowest_node_dist(t_node *curr)
{
	t_list	*l_link;
	t_link	*link;
	t_node	*node;
	int		val;
	t_node	*buff;

	val = -1;
	l_link = curr->link;
	buff = NULL;
	while (l_link)
	{
		link = l_link->content;
		node = (t_node*)link->node->content;
		if ((val == -1 || node->dist < val)
				&& node->dist != -1)
		{
			val = node->dist;
			buff = node;
		}
		l_link = l_link->next;
	}
	return (buff);
}

t_list	*lm_fetch_path2(t_list *path, t_list *curr)
{
	t_node	*node;

	node = curr->content;
	while (node && node->status != 1)
	{
		ft_lstadd(&path, ft_lstnew(node, sizeof(t_node)));
		node = lm_lowest_node_dist(node);
	}
	if (node && node->status == 1)
		ft_lstadd(&path, ft_lstnew(node, sizeof(t_node)));
	return (path);
}

t_list	*lm_find_one_path(t_data *data)
{
	t_list	*end;
	t_list	*path;

	path = NULL;
	if ((end = lm_get_end_node(data->node)) == NULL)
		return (NULL);
	path = lm_fetch_path2(path, end);
	return (path);
}
