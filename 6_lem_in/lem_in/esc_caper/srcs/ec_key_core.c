/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_key_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:53:26 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 15:59:56 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_mlx	ec_key_action(int key_hook, t_mlx mlx)
{
	if (key_hook == 69)
		mlx = ec_key_sc_plus(mlx);
	if (key_hook == 78)
		mlx = ec_key_sc_moin(mlx);
	if (key_hook == 83)
		mlx = ec_key_rx(mlx);
	if (key_hook == 84)
		mlx = ec_key_ry(mlx);
	if (key_hook == 85)
		mlx = ec_key_rz(mlx);
	if (key_hook == 86)
		mlx = ec_key_rmx(mlx);
	if (key_hook == 87)
		mlx = ec_key_rmy(mlx);
	if (key_hook == 88)
		mlx = ec_key_rmz(mlx);
	return (mlx);
}
