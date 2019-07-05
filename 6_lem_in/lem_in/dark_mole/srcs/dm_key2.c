/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_key2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:05:45 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/27 13:01:46 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

t_mlx	btn_ant_up(t_mlx mlx)
{
	mlx.cnf.nb_ant++;
	return (mlx);
}

t_mlx	btn_ant_down(t_mlx mlx)
{
	if (mlx.cnf.nb_ant > 0)
		mlx.cnf.nb_ant--;
	return (mlx);
}

t_mlx	btn_reset_map(t_mlx mlx)
{
	mlx.cnf = cnf_reset_tnls(mlx.cnf);
	mlx.cnf = cnf_reset_nodes(mlx.cnf);
	return (mlx);
}

t_mlx	btn_add_start(t_mlx mlx)
{
	t_list	*list;
	t_btn	*btn;

	list = mlx.cnf.btn;
	while (list)
	{
		btn = list->content;
		if (btn->id == 10 && btn->status == 0)
		{
			btn->status = 1;
			mlx.cnf.status = 1;
		}
		else
		{
			if (btn->id != 7)
				btn->status = 0;
			if (btn->id == 10)
				mlx.cnf.status = 0;
		}
		list = list->next;
	}
	return (mlx);
}

t_mlx	btn_add_end(t_mlx mlx)
{
	t_list	*list;
	t_btn	*btn;

	list = mlx.cnf.btn;
	while (list)
	{
		btn = list->content;
		if (btn->id == 11 && btn->status == 0)
		{
			btn->status = 1;
			mlx.cnf.status = 2;
		}
		else
		{
			if (btn->id != 7)
				btn->status = 0;
			if (btn->id == 11)
				mlx.cnf.status = 0;
		}
		list = list->next;
	}
	return (mlx);
}
