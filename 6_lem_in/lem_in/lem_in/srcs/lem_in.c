/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:10:31 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/20 15:27:12 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_data	lm_init_data(void)
{
	t_data	new;

	new.cmd = NULL;
	new.node = NULL;
	new.path = NULL;
	new.nb_ants = 0;
	new.buff = 0;
	return (new);
}

void	lm_print(t_list *list)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		L(node->id);
		list = list->next;
	}
}

int		main(void)
{
	t_data	data;
	t_list	*path;

	data = lm_init_data();
	data = lm_fetch_data(data);
	path = NULL;
	if (lm_check_data(&data))
	{
		ft_putendl(data.cmd);
		path = lm_find_one_path(&data);
		if (path)
			lm_output(path, data.nb_ants);
	}
	else
		ft_putendl("ERROR");
	lm_destroy_data(data);
	return (0);
}
