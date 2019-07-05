/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:43:46 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/20 12:50:29 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lm_chk_node_name(char *s, char c, t_list *list)
{
	int		i;
	t_node	*node;

	i = 0;
	if (*s == 'L')
		return (0);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (0);
	while (list)
	{
		node = list->content;
		if (ft_strcmp(node->id, s) == 0)
			return (0);
		list = list->next;
	}
	return (1);
}

t_list	*lm_add_node(t_list *list, char **tab, int status)
{
	t_node	node;

	node.id = ft_strdup(tab[0]);
	node.x = ft_atoi(tab[1]);
	node.y = ft_atoi(tab[2]);
	node.status = status;
	node.link = NULL;
	node.dist = -1;
	node.link_count = 0;
	ft_lstaddend(&list, ft_lstnew(&node, sizeof(t_node)));
	return (list);
}

t_data	lm_extract_node(t_data data, int *status, char **line)
{
	char	**tab;

	tab = ft_strsplit(*line, ' ');
	if (ft_strtabsize(tab) == 3 && ft_strisdig(tab[1]) == 1
			&& ft_strisdig(tab[2]) == 1)
	{
		if (lm_chk_node_name(tab[0], '-', data.node))
			data.node = lm_add_node(data.node, tab, data.buff);
		else
			*status = 3;
	}
	else
		data = lm_fetch_link(data, status, line);
	if (tab)
		lm_destroy_tab(tab);
	return (data);
}

t_data	lm_fetch_node(t_data data, int *status, char **line)
{
	int		pos;

	*status = 1;
	if ((pos = lm_line_is_status(*line)) != 0)
	{
		if (pos != -1)
			data.buff = pos;
	}
	else
	{
		data = lm_extract_node(data, status, line);
		data.buff = 0;
	}
	return (data);
}

t_data	lm_parse_nodes(t_data data, int *status, char **line)
{
	if (ft_gnl(0, line) > 0 && *line)
	{
		if (lm_line_is_com(*line))
			return (data);
		data = lm_fetch_node(data, status, line);
	}
	else
		*status = 3;
	return (data);
}
