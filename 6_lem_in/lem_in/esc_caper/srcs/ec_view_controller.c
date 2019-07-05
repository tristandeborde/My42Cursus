/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_view_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:18:13 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/20 12:48:05 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

int		refresh(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	*mlx = ec_data_to_img(*mlx);
	*mlx = ec_time_update(*mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

int		actions(int key_hook, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	*mlx = ec_key_action(key_hook, *mlx);
	if (key_hook == 53)
	{
		ec_cnf_destroy(&(mlx->cnf));
		mlx_destroy_window(mlx, mlx->win);
		exit(1);
	}
	return (0);
}

int		mouse_on(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (button == 1 && x > 0 && x < 1000 && y > 0)
	{
		mlx->cnf.click = 1;
		mlx->cnf.sx = x;
		mlx->cnf.sy = y;
	}
	return (0);
}

int		mouse(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (button == 1 && (x != 0 || y != 0))
		mlx->cnf.click = 0;
	return (0);
}

int		drag_drop(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (mlx->cnf.click == 1)
	{
		mlx->cnf.ox += x - mlx->cnf.sx;
		mlx->cnf.oy += y - mlx->cnf.sy;
		mlx->cnf.sx = x;
		mlx->cnf.sy = y;
	}
	return (0);
}
