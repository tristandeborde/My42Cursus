/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:47:39 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/01 18:19:10 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_dos	**ec_getsphere_coords(t_dos **map, int r, t_dos p)
{
	t_dos	b;
	t_ang	a;
	int		i;
	int		j;

	i = 0;
	b.x = (double)r;
	b.y = 0.0;
	b.z = 0.0;
	a = set_ang(0, 0, 0);
	while (i < 18)
	{
		j = 0;
		while (j < 10)
		{
			map[i][j] = ec_doff_set(ec_rotate_all(a, b), p);
			a = ec_up_y(a, 20);
			j++;
		}
		a = ec_up_y(a, 160);
		a = ec_up_x(a, 20);
		i++;
	}
	return (map);
}

t_pos	**ec_pos_sphere(t_mlx mlx, int r, t_dos d, t_pos **map2)
{
	t_dos	**map;
	t_dos	p;
	int		i;
	int		j;

	map = ec_new_dmap();
	map = ec_getsphere_coords(map, r, d);
	i = 0;
	while (i < 18)
	{
		j = 0;
		while (j < 10)
		{
			p = map[i][j];
			if ((j == 0 || j == 9) && i != 0)
				map2[i][j] = map2[i - 1][j];
			else
				map2[i][j] = rot_2d(mlx.cnf, p);
			j++;
		}
		i++;
	}
	ec_destroy_dmap(map);
	return (map2);
}

t_img	line_sphere(t_img img, t_pos **map, int i, int j)
{
	t_pos	p1;
	t_pos	p2;

	p1 = map[i][j];
	if (j < 9)
	{
		p2 = map[i][j + 1];
		img = line(img, p1, p2, 0xffffff);
	}
	if (i == 17)
		p2 = map[0][j];
	else
		p2 = map[i + 1][j];
	img = line(img, p1, p2, 0xffffff);
	return (img);
}

t_img	ec_draw_sphere(t_mlx mlx, int r, t_dos d)
{
	t_pos	**map;
	int		i;
	int		j;

	map = ec_new_pmap();
	map = ec_pos_sphere(mlx, r, d, map);
	i = 0;
	while (i < 18)
	{
		j = 0;
		while (j < 10)
		{
			mlx.img = line_sphere(mlx.img, map, i, j);
			j++;
		}
		i++;
	}
	ec_destroy_pmap(map);
	return (mlx.img);
}
