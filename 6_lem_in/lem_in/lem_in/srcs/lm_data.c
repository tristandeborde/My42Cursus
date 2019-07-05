/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:36:29 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/13 11:27:20 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lm_destroy_link(t_list *link)
{
	t_list	*elem;

	elem = link;
	while (elem)
	{
		free(elem->content);
		link = elem->next;
		free(elem);
		elem = link;
	}
}

void	lm_destroy_node(t_list *node)
{
	t_node	*elem;

	elem = node->content;
	lm_destroy_link(elem->link);
	if (elem->id)
		free(elem->id);
	free(node->content);
}

void	lm_destroy_data(t_data data)
{
	t_list	*node;
	t_list	*buff;

	if (data.cmd)
		free(data.cmd);
	node = data.node;
	while (node)
	{
		buff = node->next;
		lm_destroy_node(node);
		node = buff;
	}
}
