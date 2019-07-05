/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_parse_ant.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:32:14 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 15:51:51 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_list	*ec_format_ant(int id)
{
	t_ant	ant;
	t_list	*list;

	ant.id = id;
	ant.id_pos = 0;
	ant.id_dst = 0;
	ant.pos = stpd(0, 0, 0);
	list = ft_lstnew(&ant, sizeof(t_ant));
	return (list);
}

t_list	*ec_add_ants(t_list *list, int nb)
{
	int		i;

	i = 0;
	list = NULL;
	while (i < nb)
	{
		ft_lstaddend(&list, ec_format_ant(i + 1));
		i++;
	}
	return (list);
}

t_cnf	ec_fetch_ant(t_cnf cnf, int *status, char **line)
{
	int		nb;

	*status = 0;
	if (ft_strisdig(*line))
	{
		nb = ft_atoi(*line);
		cnf.ant = ec_add_ants(cnf.ant, nb);
	}
	else
		cnf = ec_fetch_node(cnf, status, line);
	return (cnf);
}

t_cnf	ec_parse_ants(t_cnf cnf, int *status, char **line)
{
	if (ft_gnl(0, line) > 0 && *line)
	{
		if (ec_line_is_com(*line))
			return (cnf);
		cnf = ec_fetch_ant(cnf, status, line);
	}
	else
		*status = 4;
	return (cnf);
}
