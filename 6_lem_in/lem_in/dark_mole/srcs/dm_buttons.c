/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 14:38:44 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/25 18:08:31 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

int		dm_btn_next_id(t_list *list)
{
	t_btn	*btn;

	if (list)
	{
		while (list->next)
			list = list->next;
		btn = list->content;
		return (btn->id + 1);
	}
	return (1);
}

int		dm_btn_next_oy(t_list *list)
{
	t_btn	*btn;

	if (list)
	{
		while (list->next)
			list = list->next;
		btn = list->content;
		return (btn->oy + btn->y + 20);
	}
	return (20);
}

t_list	*dm_add_button(t_list *list, char *name, int type, int size)
{
	t_btn	btn;

	btn.id = dm_btn_next_id(list);
	btn.label = ft_strdup(name);
	btn.type = type;
	btn.status = 0;
	btn.ox = 1020;
	btn.oy = dm_btn_next_oy(list);
	btn.x = 160;
	btn.y = size;
	btn.color1 = 0x55841f;
	btn.color2 = 0xe53f05;
	ft_lstaddend(&(list), ft_lstnew(&btn, sizeof(t_btn)));
	return (list);
}
