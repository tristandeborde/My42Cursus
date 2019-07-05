/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_sphere_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:17:26 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/01 18:31:56 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_ang	ec_up_x(t_ang a, int ang)
{
	a.x += (double)ang * M_PI / 180.0;
	return (a);
}

t_ang	ec_up_y(t_ang a, int ang)
{
	a.y += (double)ang * M_PI / 180.0;
	return (a);
}

t_dos	ec_rotate_all(t_ang a, t_dos b)
{
	t_dos	p;

	p.x = rotate_x(a, b.x, b.y, b.z);
	p.y = rotate_y(a, b.x, b.y, b.z);
	p.z = rotate_z(a, b.x, b.y, b.z);
	return (p);
}

t_dos	ec_doff_set(t_dos p1, t_dos p2)
{
	p1.x += p2.x;
	p1.y += p2.y;
	p1.z += p2.z;
	return (p1);
}
