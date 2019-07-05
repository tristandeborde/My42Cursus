/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_key1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:27:49 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/28 16:01:34 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_mlx	ec_key_sc_plus(t_mlx mlx)
{
	mlx.cnf.scale += 0.1;
	return (mlx);
}

t_mlx	ec_key_sc_moin(t_mlx mlx)
{
	if (mlx.cnf.scale > 1.1)
		mlx.cnf.scale -= 0.1;
	return (mlx);
}

t_mlx	ec_key_rx(t_mlx mlx)
{
	mlx.cnf.ax++;
	mlx.cnf.ax = mlx.cnf.ax % 360;
	return (mlx);
}

t_mlx	ec_key_ry(t_mlx mlx)
{
	mlx.cnf.ay++;
	mlx.cnf.ay = mlx.cnf.ay % 360;
	return (mlx);
}

t_mlx	ec_key_rz(t_mlx mlx)
{
	mlx.cnf.az++;
	mlx.cnf.az = mlx.cnf.az % 360;
	return (mlx);
}
