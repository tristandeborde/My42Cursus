/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 10:11:42 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 18:32:05 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_img	circle(t_img img, t_pos p, int radius, int color)
{
	int			x;
	int			y;
	int			a;
	double		rad;
	int			i;

	a = 0;
	while (a < 180)
	{
		rad = (double)a * M_PI / 180.0;
		x = (int)(cos(rad) * (double)radius) + p.x;
		y = (int)(sin(rad) * (double)radius) + p.y;
		i = (int)(sin((double)(360 - a) * M_PI / 180.0) * (double)radius) + p.y;
		while (i <= y)
		{
			if (x < 1000)
				img = set_img_pxl(img, x, i, color);
			i++;
		}
		a++;
	}
	return (img);
}

t_pos	ec_ant_pos(t_dos p1, t_dos p2, t_cnf cnf)
{
	t_pos	p;
	t_dos	buff;
	int		time;

	time = cnf.time;
	buff.x = (p1.x - p2.x) / 180.0 * (double)time + p2.x;
	buff.y = (p1.y - p2.y) / 180.0 * (double)time + p2.y;
	buff.z = 0;
	p = rot_2d(cnf, buff);
	return (p);
}

t_mlx	ec_draw_ping(t_mlx mlx, t_dos p1, t_dos p2, int type)
{
	int		set;
	int		i;
	int		color;
	int		radius;

	set = (mlx.cnf.time % 60) / 6 + 1;
	i = 1;
	while (--set)
	{
		radius = 10 * set / 10;
		color = (255 * i / 10) << type;
		mlx.img = circle(mlx.img, ec_ant_pos(p1, p2, mlx.cnf), radius, color);
		i++;
	}
	return (mlx);
}

t_mlx	ec_time_update(t_mlx mlx)
{
	int		round;

	round = 180;
	if (mlx.cnf.ant_sts == 1)
		round = 60;
	mlx.cnf.time = (mlx.cnf.time + 1) % round;
	if (mlx.cnf.time == 0)
		mlx = ec_update_timer_status(mlx);
	if (mlx.cnf.ant_sts == 0)
		mlx = ec_ping_move(mlx);
	else
		mlx = ec_ping_hold(mlx);
	return (mlx);
}
