/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_key1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 18:34:40 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/26 19:28:33 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

t_mlx	scale_up(t_mlx mlx)
{
	if (mlx.cnf.grid_size < 200)
		mlx.cnf.grid_size++;
	return (mlx);
}

t_mlx	scale_down(t_mlx mlx)
{
	if (mlx.cnf.grid_size > 10)
		mlx.cnf.grid_size--;
	return (mlx);
}

t_mlx	btn_add_node(t_mlx mlx)
{
	t_list	*list;
	t_btn	*btn;

	list = mlx.cnf.btn;
	while (list)
	{
		btn = list->content;
		if (btn->id == 7 && btn->status == 0)
			btn->status = 1;
		else
		{
			if (btn->type == 2)
				btn->status = 0;
		}
		list = list->next;
	}
	return (mlx);
}

t_mlx	btn_add_tnl(t_mlx mlx)
{
	t_list	*list;
	t_btn	*btn;

	list = mlx.cnf.btn;
	while (list)
	{
		btn = list->content;
		if (btn->id == 8 && btn->status == 0)
			btn->status = 1;
		else
		{
			btn->status = 0;
		}
		list = list->next;
	}
	return (mlx);
}
