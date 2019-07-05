/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_controller_fcts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:42:07 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/26 16:42:08 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

int		dm_find_button(t_mlx *mlx, int y)
{
	t_list	*list;
	t_btn	*btn;

	list = mlx->cnf.btn;
	while (list)
	{
		btn = list->content;
		if (y > btn->oy && y < (btn->oy + btn->y) && btn->type != 0)
			return (btn->id);
		list = list->next;
	}
	return (0);
}
