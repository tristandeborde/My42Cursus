/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_cnf_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:00:16 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 16:09:14 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

void	ec_destroy_ants(t_list *list)
{
	t_list	*buff;
	t_ant	*ant;

	while (list)
	{
		ant = list->content;
		free(ant);
		buff = list->next;
		free(list);
		list = buff;
	}
}

void	ec_destroy_nodes(t_list *list)
{
	t_list	*buff;
	t_node	*node;

	while (list)
	{
		node = list->content;
		free(node->label);
		free(node);
		buff = list->next;
		free(list);
		list = buff;
	}
}

void	ec_destroy_links(t_list *list)
{
	t_list	*buff;
	t_link	*link;

	while (list)
	{
		link = list->content;
		free(link);
		buff = list->next;
		free(list);
		list = buff;
	}
}

void	ec_cnf_destroy(t_cnf *cnf)
{
	ec_destroy_ants(cnf->ant);
	ec_destroy_links(cnf->link);
	ec_destroy_nodes(cnf->node);
	cnf->ant = NULL;
	cnf->node = NULL;
	cnf->link = NULL;
}
