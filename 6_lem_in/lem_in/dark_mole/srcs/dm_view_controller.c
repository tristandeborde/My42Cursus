/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_view_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:51:35 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 16:33:20 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

int		refresh(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	*mlx = dm_data_to_img(*mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	dm_menu_txt(mlx);
	return (0);
}

int		actions(int key_hook, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (key_hook == 53)
	{
		mlx->cnf = cnf_reset_tnls(mlx->cnf);
		mlx->cnf = cnf_reset_nodes(mlx->cnf);
		dm_destroy_buttons(&(mlx->cnf));
		mlx_destroy_window(mlx, mlx->win);
		exit(1);
	}
	return (0);
}

int		mouse_on(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (button == 1 && x > 0 && x < 1000 && y > 0
			&& dm_clicked_btn(*mlx) == 0)
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
	int		n;

	mlx = (t_mlx*)param;
	if (button == 1 && x > 1020 && x < 1180)
	{
		n = dm_find_button(mlx, y);
		if (n != 0)
			*mlx = dm_key_action(n, *mlx);
	}
	if (button == 1 && x > 0 && x < 1000)
		*mlx = cnf_add_map(*mlx, x, y);
	*mlx = dm_free_bad_tnl(*mlx);
	*mlx = dm_draw_menu(*mlx);
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
