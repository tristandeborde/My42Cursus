/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_caper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:11:49 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/04 18:38:41 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_cnf	cnf_init(void)
{
	t_cnf		cnf;

	cnf.ant_sts = 0;
	cnf.time = 1;
	cnf.ox = 500;
	cnf.oy = 500;
	cnf.sx = 0;
	cnf.sy = 0;
	cnf.ax = 52;
	cnf.ay = 25;
	cnf.az = 0;
	cnf.scale = 5;
	cnf.click = 0;
	cnf.buff = 0;
	cnf = ec_parser(cnf);
	return (cnf);
}

t_mlx	esc_caper_init(t_cnf cnf)
{
	t_mlx	mlx;
	size_t	size_x;
	size_t	size_y;

	size_x = 1000;
	size_y = 1000;
	mlx.mlx = mlx_init();
	mlx.cnf = cnf;
	mlx.img.size_column = size_y;
	mlx.win = mlx_new_window(mlx.mlx, size_x, size_y, "esc-caper");
	mlx.img.img = mlx_new_image(mlx.mlx, size_x, size_y);
	mlx.img.data = (int*)mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, \
			&mlx.img.size_line, &mlx.img.endian);
	return (mlx);
}

int		main(void)
{
	t_mlx	mlx;
	t_cnf	cnf;

	cnf = cnf_init();
	mlx = esc_caper_init(cnf);
	mlx = ec_data_to_img(mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_hook(mlx.win, 2, (1L << 0), actions, &mlx);
	mlx_hook(mlx.win, 4, (1L << 3), mouse_on, &mlx);
	mlx_hook(mlx.win, 5, (1L << 3), mouse, &mlx);
	mlx_hook(mlx.win, 6, (1L << 2), drag_drop, &mlx);
	mlx_loop_hook(mlx.mlx, refresh, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
