/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:32:31 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 15:51:40 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_cnf	ec_extract_link(t_cnf cnf, int id1, int id2)
{
	t_link	link;

	link.id1 = id1;
	link.id2 = id2;
	ft_lstaddend(&(cnf.link), ft_lstnew(&link, sizeof(t_link)));
	return (cnf);
}

t_cnf	ec_fetch_link(t_cnf cnf, int *status, char **line)
{
	char	**tab;
	int		node1;
	int		node2;

	*status = 2;
	tab = ft_strsplit(*line, '-');
	if (ft_strtabsize(tab) == 2 && ft_strcmp(tab[0], tab[1]) != 0)
	{
		if ((node1 = ec_node_id_by_name(cnf, tab[0]))
				&& (node2 = ec_node_id_by_name(cnf, tab[1])))
		{
			cnf = ec_extract_link(cnf, node1, node2);
		}
		else
			*status = 3;
	}
	else
		*status = 3;
	ec_destroy_tab(tab);
	return (cnf);
}

t_cnf	ec_parse_links(t_cnf cnf, int *status, char **line)
{
	if (ft_gnl(0, line) > 0 && *line)
	{
		if (ec_line_is_com(*line))
			return (cnf);
		cnf = ec_fetch_link(cnf, status, line);
	}
	else
		*status = 4;
	return (cnf);
}
