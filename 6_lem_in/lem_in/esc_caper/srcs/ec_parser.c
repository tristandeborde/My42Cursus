/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:49:43 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/20 12:47:46 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_cnf	ec_init_cnf_lst(t_cnf cnf)
{
	cnf.node = NULL;
	cnf.link = NULL;
	cnf.ant = NULL;
	return (cnf);
}

int		ec_start_id(t_cnf cnf, t_dos *p)
{
	t_node	*node;
	t_list	*list;

	list = cnf.node;
	while (list)
	{
		node = list->content;
		if (node->status == 1)
		{
			*p = stpd(node->x, node->y, node->z);
			return (node->id);
		}
		list = list->next;
	}
	return (0);
}

t_cnf	ec_link_pos(t_cnf cnf)
{
	t_list	*list;
	t_link	*link;

	list = cnf.link;
	while (list)
	{
		link = list->content;
		link->p1 = ec_node_dos(cnf.node, link->id1);
		link->p2 = ec_node_dos(cnf.node, link->id2);
		list = list->next;
	}
	return (cnf);
}

t_cnf	ec_set_start(t_cnf cnf)
{
	t_ant	*ant;
	t_list	*list;
	int		id;
	t_dos	p;

	p = stpd(0, 0, 0);
	id = ec_start_id(cnf, &p);
	list = cnf.ant;
	while (list)
	{
		ant = list->content;
		ant->id_pos = id;
		ant->pos = p;
		list = list->next;
	}
	return (cnf);
}

t_cnf	ec_parser(t_cnf cnf)
{
	int		status;

	status = 0;
	cnf = ec_init_cnf_lst(cnf);
	cnf = ec_fetch_cnf(cnf, &status);
	cnf = ec_link_pos(cnf);
	cnf = ec_set_start(cnf);
	return (cnf);
}
