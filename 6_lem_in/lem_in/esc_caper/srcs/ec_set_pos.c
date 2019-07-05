/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_set_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:16:46 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/28 11:16:47 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_dos	stpd(int x, int y, int z)
{
	t_dos	p;

	p.x = (double)x;
	p.y = (double)y;
	p.z = (double)z;
	return (p);
}

t_pos	stp3(int x, int y, int z)
{
	t_pos	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_ang	set_ang(int ax, int ay, int az)
{
	t_ang	a;

	a.x = ((double)ax * M_PI) / 180.0;
	a.y = ((double)ay * M_PI) / 180.0;
	a.z = ((double)az * M_PI) / 180.0;
	return (a);
}

t_dos	ec_scale_pos(t_dos p, int x)
{
	p.x *= (double)x;
	p.y *= (double)x;
	p.z *= (double)x;
	return (p);
}
