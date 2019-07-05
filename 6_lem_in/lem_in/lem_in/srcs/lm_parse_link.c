/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:32:31 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/14 14:41:07 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_data	lm_extract_link(t_data data, t_list *elem1, t_list *elem2)
{
	t_link	link1;
	t_link	link2;
	t_node	*node1;
	t_node	*node2;

	link1.node = elem2;
	link1.val = 0;
	node1 = elem1->content;
	ft_lstaddend(&(node1->link), ft_lstnew(&link1, sizeof(t_link)));
	link2.node = elem1;
	link2.val = 0;
	node2 = elem2->content;
	ft_lstaddend(&(node2->link), ft_lstnew(&link2, sizeof(t_link)));
	return (data);
}

int		lm_check_link(t_list *node1, t_list *node2)
{
	t_node	*node;
	t_list	*list;
	t_link	*link;

	node = node1->content;
	list = node->link;
	while (list)
	{
		link = list->content;
		if (link->node == node2)
			return (0);
		list = list->next;
	}
	return (1);
}

t_data	lm_fetch_link(t_data data, int *status, char **line)
{
	char	**tab;
	t_list	*node1;
	t_list	*node2;

	*status = 2;
	tab = ft_strsplit(*line, '-');
	if (ft_strtabsize(tab) == 2 && ft_strcmp(tab[0], tab[1]) != 0
			&& (((node1 = lm_node_by_name(data, tab[0]))
			&& (node2 = lm_node_by_name(data, tab[1])))))
	{
		if (lm_check_link(node1, node2))
			data = lm_extract_link(data, node1, node2);
	}
	else
		*status = 3;
	lm_destroy_tab(tab);
	return (data);
}

t_data	lm_parse_links(t_data data, int *status, char **line)
{
	if (ft_gnl(0, line) > 0 && *line)
	{
		if (lm_line_is_com(*line))
			return (data);
		data = lm_fetch_link(data, status, line);
	}
	else
		*status = 3;
	return (data);
}
