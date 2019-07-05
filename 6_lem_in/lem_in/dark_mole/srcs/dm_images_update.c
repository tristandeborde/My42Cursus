/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_images_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:51:08 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/26 17:43:22 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

t_img	reset_img(t_img img)
{
	int		i;
	int		j;
	int		color;

	i = 0;
	while (i < img.size_column)
	{
		j = 0;
		while (j < img.size_line / 4)
		{
			color = img.data[i * img.size_line / 4 + j];
			if (j < 1000)
			{
				color = 0x381f0a;
				img = set_img_pxl(img, j, i, color);
			}
			j++;
		}
		i++;
	}
	return (img);
}

t_img	dm_draw_box(t_img img, t_pos p1, t_pos p2, int color)
{
	int ox;
	int oy;
	int x;
	int y;

	ox = p1.x;
	oy = p1.y;
	x = p2.x;
	y = p2.y;
	img = line(img, stp(ox, oy), stp(ox, oy + y), color);
	img = line(img, stp(ox, oy), stp(ox + x, oy), color);
	img = line(img, stp(ox + x, oy), stp(ox + x, oy + y), color);
	img = line(img, stp(ox, oy + y), stp(ox + x, oy + y), color);
	return (img);
}

t_img	dm_init_grid(t_img img, int size, t_cnf cnf)
{
	int		i;
	int		x;
	int		buff;

	i = 1000 / size;
	x = ((1000 - i * size) / 2 + cnf.oy) % i;
	buff = size;
	while (--buff > 0)
	{
		x += i;
		img = line(img, stp(0, x), stp(1000, x), 0x5f4b3a);
	}
	x = ((1000 - i * size) / 2 + cnf.ox) % i;
	buff = size;
	while (--buff > 0)
	{
		x += i;
		img = line(img, stp(x, 0), stp(x, 1000), 0x5f4b3a);
	}
	return (img);
}

t_mlx	dm_init_img(t_mlx mlx)
{
	mlx.img = reset_img(mlx.img);
	mlx.img = line(mlx.img, stp(1001, 0), stp(1001, 1000), 0xffffff);
	mlx.img = dm_init_grid(mlx.img, mlx.cnf.grid_size, mlx.cnf);
	return (mlx);
}

t_mlx	dm_data_to_img(t_mlx mlx)
{
	mlx = dm_init_img(mlx);
	mlx = dm_draw_tnls(mlx);
	mlx = dm_draw_nodes(mlx);
	return (mlx);
}
