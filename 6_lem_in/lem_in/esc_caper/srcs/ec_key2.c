/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_key2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 10:29:27 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/28 10:31:56 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_mlx	ec_key_rmx(t_mlx mlx)
{
	mlx.cnf.ax--;
	if (mlx.cnf.ax == -1)
		mlx.cnf.ax = 359;
	return (mlx);
}

t_mlx	ec_key_rmy(t_mlx mlx)
{
	mlx.cnf.ay--;
	if (mlx.cnf.ay == -1)
		mlx.cnf.ay = 359;
	return (mlx);
}

t_mlx	ec_key_rmz(t_mlx mlx)
{
	mlx.cnf.az--;
	if (mlx.cnf.az == -1)
		mlx.cnf.az = 359;
	return (mlx);
}
