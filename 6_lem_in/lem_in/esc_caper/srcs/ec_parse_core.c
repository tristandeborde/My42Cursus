/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parse_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:36:10 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 15:52:00 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_list	*ec_add_cmd(t_cnf cnf, char *s, int *status, int id)
{
	char	**tab;
	t_cmd	cmd;
	t_ant	*ant;
	t_node	*node;

	tab = ft_strsplit(s, '-');
	if (ft_strtabsize(tab) == 2 && (ant = ec_check_ant_id(cnf.ant, tab[0]))
			&& (node = ec_check_node_name(cnf.node, tab[1])))
	{
		cmd.id = id;
		cmd.dst = node;
		cmd.ant = ant;
		ft_lstaddend(&(cnf.cmd), ft_lstnew(&cmd, sizeof(t_cmd)));
	}
	else
		*status = 2;
	if (tab)
		ec_destroy_tab(tab);
	return (cnf.cmd);
}

t_cnf	parse_cmd(t_cnf cnf, char *line, int *status)
{
	char	**tab;
	int		i;
	int		id;

	tab = ft_strsplit(line, ' ');
	i = 0;
	id = ec_cmd_new_id(cnf.cmd);
	while (tab[i] && *status == 1)
	{
		cnf.cmd = ec_add_cmd(cnf, tab[i], status, id);
		i++;
	}
	if (tab)
		ec_destroy_tab(tab);
	return (cnf);
}

t_cnf	ec_fetch_cmd(t_cnf cnf)
{
	char	*line;
	int		status;

	status = 0;
	while (status < 2)
	{
		if (ft_gnl(0, &line) > 0)
		{
			if (line[0] == 'L' && (status == 0 || status == 1))
			{
				status = 1;
				cnf = parse_cmd(cnf, line, &status);
			}
			else if (line[0] != 'L' && status == 1)
				status = 2;
		}
		else
			status = 2;
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	return (cnf);
}

t_cnf	ec_fetch_cnf(t_cnf cnf, int *status)
{
	t_parse	*parse;
	char	*line;

	parse = ec_getparse();
	line = NULL;
	while (*status < 3)
	{
		cnf = parse[*status].f(cnf, status, &line);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (*status < 4)
		cnf = ec_fetch_cmd(cnf);
	return (cnf);
}
