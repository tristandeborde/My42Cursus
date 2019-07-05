/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_rev_euler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 11:34:34 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/03 19:31:54 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

double	ec_vect_len(t_dos p1, t_dos p2)
{
	double	len;

	p2.x -= p1.x;
	p2.y -= p1.y;
	p2.z -= p1.z;
	len = sqrt(p2.x * p2.x + p2.y * p2.y + p2.z * p2.z);
	return (len);
}

double	ec_sgn_crossprod(double x1, double y1, double x2, double y2)
{
	double	prod;

	prod = x1 * y2 - x2 * y1;
	if (prod < 0)
		return (-1.0);
	return (1.0);
}

t_ang	ec_rev_euler(t_dos p1, t_dos p2)
{
	t_ang	a;
	double	cos_theta;
	double	cos_sigma;
	t_dos	abs;

	abs.x = 0.0;
	abs.y = 0.0;
	abs.z = ec_vect_len(p1, p2);
	p2.x -= p1.x;
	p2.y -= p1.y;
	p2.z -= p1.z;
	cos_theta = -1.0 * atan2(p2.y, p2.z) - 0.085;
	cos_sigma = -1.0 * atan2(p2.x, p2.z);
	a.x = cos_theta;
	a.z = cos_sigma;
	a.y = cos_sigma;
	return (a);
}
