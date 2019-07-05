/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_check_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 17:25:22 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/14 16:08:09 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lm_check_ant_nb(int nb)
{
	if (nb < 1)
		return (0);
	return (1);
}

int		lm_check_start_end(t_list *list)
{
	t_node	*node;
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (list)
	{
		node = list->content;
		if (node->status == 1)
			start++;
		if (node->status == 2)
			end++;
		list = list->next;
	}
	if (start == 1 && end == 1)
		return (1);
	return (0);
}

t_list	*lm_get_end_node(t_list *list)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		if (node->status == 2)
			return (list);
		list = list->next;
	}
	return (NULL);
}

int		lm_check_ok_path2(t_list *list)
{
	t_list	*end;
	t_list	*l_link;
	t_link	*link;
	t_node	*node;

	if ((end = lm_get_end_node(list)) == NULL)
		return (0);
	l_link = ((t_node*)end->content)->link;
	while (l_link)
	{
		link = l_link->content;
		node = link->node->content;
		if (node->dist != -1)
			return (1);
		l_link = l_link->next;
	}
	return (0);
}

int		lm_check_data(t_data *data)
{
	if (lm_check_ant_nb(data->nb_ants) == 0
			|| lm_check_start_end(data->node) == 0)
		return (0);
	lm_link_vals_fill(data);
	if (lm_check_ok_path2(data->node) == 0)
		return (0);
	return (1);
}
