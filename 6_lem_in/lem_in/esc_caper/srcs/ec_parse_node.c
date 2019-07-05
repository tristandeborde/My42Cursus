/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:43:46 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 15:51:31 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

int		ec_line_is_status(char *line)
{
	if (line[0] == '#' && ft_strlen(line) > 3 && line[1] == '#')
	{
		if (ft_strcmp(line, "##end") == 0)
			return (2);
		if (ft_strcmp(line, "##start") == 0)
			return (1);
		return (-1);
	}
	return (0);
}

int		ec_node_fresh_id(t_list *list)
{
	t_node	*node;

	if (list)
	{
		while (list->next)
			list = list->next;
		node = list->content;
		return (node->id + 1);
	}
	return (1);
}

t_cnf	ec_extract_node(t_cnf cnf, int *status, char **line)
{
	char	**tab;
	t_node	node;

	tab = ft_strsplit(*line, ' ');
	if (ft_strtabsize(tab) == 3 && ft_strisdig(tab[1]) == 1
			&& ft_strisdig(tab[2]) == 1)
	{
		if (ec_chk_node_name(tab[0], '-'))
		{
			node.id = ec_node_fresh_id(cnf.node);
			node.label = ft_strdup(tab[0]);
			node.x = ft_atoi(tab[1]);
			node.y = ft_atoi(tab[2]);
			node.z = 0;
			node.status = cnf.buff;
			ft_lstaddend(&(cnf.node), ft_lstnew(&node, sizeof(t_node)));
		}
		else
			*status = 3;
	}
	else
		cnf = ec_fetch_link(cnf, status, line);
	if (tab)
		ec_destroy_tab(tab);
	return (cnf);
}

t_cnf	ec_fetch_node(t_cnf cnf, int *status, char **line)
{
	int		pos;

	*status = 1;
	if ((pos = ec_line_is_status(*line)) != 0)
	{
		if (cnf.buff != 0)
			*status = 3;
		cnf.buff = pos;
	}
	else
	{
		cnf = ec_extract_node(cnf, status, line);
		cnf.buff = 0;
	}
	return (cnf);
}

t_cnf	ec_parse_nodes(t_cnf cnf, int *status, char **line)
{
	if (ft_gnl(0, line) > 0 && *line)
	{
		if (ec_line_is_com(*line))
			return (cnf);
		cnf = ec_fetch_node(cnf, status, line);
	}
	else
		*status = 4;
	return (cnf);
}
