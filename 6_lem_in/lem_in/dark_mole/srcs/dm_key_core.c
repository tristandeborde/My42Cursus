/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_key_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:25:10 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 16:32:29 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

t_mlx	dm_key_action(int n, t_mlx mlx)
{
	if (n == 5)
		mlx = scale_down(mlx);
	if (n == 4)
		mlx = scale_up(mlx);
	if (n == 7)
		mlx = btn_add_node(mlx);
	if (n == 8)
		mlx = btn_add_tnl(mlx);
	if (n == 10)
		mlx = btn_add_start(mlx);
	if (n == 11)
		mlx = btn_add_end(mlx);
	if (n == 14)
		mlx = btn_ant_up(mlx);
	if (n == 15)
		mlx = btn_ant_down(mlx);
	if (n == 17)
		mlx = btn_reset_map(mlx);
	if (n == 18)
		mlx = btn_output_map(mlx);
	return (mlx);
}
