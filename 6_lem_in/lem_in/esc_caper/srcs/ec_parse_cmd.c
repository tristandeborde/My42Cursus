/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:38:13 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 15:48:10 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

int		ec_cmd_new_id(t_list *list)
{
	t_cmd	*cmd;

	if (list)
	{
		while (list->next)
			list = list->next;
		cmd = list->content;
		return (cmd->id + 1);
	}
	return (1);
}

t_ant	*ec_check_ant_id(t_list *list, char *str)
{
	t_ant	*ant;
	int		id;

	id = ft_atoi(str + 1);
	while (list)
	{
		ant = list->content;
		if (ant->id == id)
			return (ant);
		list = list->next;
	}
	return (NULL);
}

t_node	*ec_check_node_name(t_list *list, char *label)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		if (ft_strcmp(node->label, label) == 0)
			return (node);
		list = list->next;
	}
	return (NULL);
}

int		ec_chk_node_name(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (0);
	return (1);
}

t_dos	ec_node_dos(t_list *list, int id)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		if (node->id == id)
			return (stpd(node->x, node->y, node->z));
		list = list->next;
	}
	return (stpd(0, 0, 0));
}
