/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_buttons_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:15:18 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 16:20:41 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

void	dm_destroy_buttons(t_cnf *cnf)
{
	t_list	*list;
	t_list	*buff;
	t_btn	*btn;

	list = cnf->btn;
	while (list)
	{
		btn = list->content;
		free(btn->label);
		free(btn);
		buff = list->next;
		free(list);
		list = buff;
	}
	cnf->btn = NULL;
}
