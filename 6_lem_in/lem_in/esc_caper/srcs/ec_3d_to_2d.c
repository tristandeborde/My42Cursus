/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_3d_to_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:59:40 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/01 16:18:11 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

double	rotate_x(t_ang a, double x, double y, double z)
{
	double	n_x;

	n_x = (cos(a.z) * cos(a.y) - sin(a.z) * cos(a.x) * sin(a.y)) * x;
	n_x += (-1.0 * cos(a.z) * sin(a.y) - sin(a.z) * cos(a.x) * cos(a.y)) * y;
	n_x += sin(a.z) * sin(a.x) * z;
	return (n_x);
}

double	rotate_y(t_ang a, double x, double y, double z)
{
	double	n_y;

	n_y = (sin(a.z) * cos(a.y) + cos(a.z) * cos(a.x) * sin(a.y)) * x;
	n_y += (-1.0 * sin(a.z) * sin(a.y) + cos(a.z) * cos(a.x) * cos(a.y)) * y;
	n_y += -1.0 * cos(a.z) * sin(a.x) * z;
	return (n_y);
}

double	rotate_z(t_ang a, double x, double y, double z)
{
	double	n_z;

	n_z = sin(a.x) * sin(a.y) * x;
	n_z += sin(a.x) * cos(a.y) * y;
	n_z += cos(a.x) * z;
	return (n_z);
}

t_pos	rot_2d(t_cnf c, t_dos d)
{
	t_pos	p;
	t_ang	a;

	a = set_ang(c.ax, c.ay, c.az);
	p.x = (int)(rotate_x(a, d.x, d.y, d.z) * c.scale) + c.ox;
	p.y = (int)(rotate_y(a, d.x, d.y, d.z) * c.scale) + c.oy;
	return (p);
}
