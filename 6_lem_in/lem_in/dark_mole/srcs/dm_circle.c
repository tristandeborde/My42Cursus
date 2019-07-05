/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_circle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 10:57:48 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/26 17:30:48 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

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
