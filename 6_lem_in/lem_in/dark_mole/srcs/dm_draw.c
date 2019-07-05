/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:53:00 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/23 15:00:11 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

t_pos	stp(int x, int y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_img	set_img_pxl(t_img img, int x, int y, int color)
{
	if (x < img.size_line / 4 && y < img.size_column && x > -1 && y > -1)
		img.data[x + (y * img.size_line / 4)] = color;
	return (img);
}

t_img	line_x(t_img img, t_pos p1, t_pos p2, int color)
{
	t_line	l;
	int		i;

	l.xi = (p2.x - p1.x > 0) ? 1 : -1;
	l.yi = (p2.y - p1.y > 0) ? 1 : -1;
	l.dx = (p2.x - p1.x) * l.xi;
	l.dy = (p2.y - p1.y) * l.yi;
	i = -1;
	l.e = l.dx / 2;
	while (++i <= l.dx)
	{
		img = set_img_pxl(img, p1.x, p1.y, color);
		p1.x += l.xi;
		l.e += l.dy;
		if (l.e > l.dx)
		{
			l.e -= l.dx;
			p1.y += l.yi;
		}
	}
	return (img);
}

t_img	line_y(t_img img, t_pos p1, t_pos p2, int color)
{
	t_line	l;
	int		i;

	l.xi = (p2.x - p1.x > 0) ? 1 : -1;
	l.yi = (p2.y - p1.y > 0) ? 1 : -1;
	l.dx = (p2.x - p1.x) * l.xi;
	l.dy = (p2.y - p1.y) * l.yi;
	i = -1;
	l.e = l.dy / 2;
	while (++i <= l.dy)
	{
		img = set_img_pxl(img, p1.x, p1.y, color);
		p1.y += l.yi;
		l.e += l.dx;
		if (l.e > l.dy)
		{
			l.e -= l.dy;
			p1.x += l.xi;
		}
	}
	return (img);
}

t_img	line(t_img img, t_pos p1, t_pos p2, int color)
{
	t_line	l;

	l.xi = (p2.x - p1.x > 0) ? 1 : -1;
	l.yi = (p2.y - p1.y > 0) ? 1 : -1;
	l.dx = (p2.x - p1.x) * l.xi;
	l.dy = (p2.y - p1.y) * l.yi;
	if (l.dx > l.dy)
		img = line_x(img, p1, p2, color);
	else
		img = line_y(img, p1, p2, color);
	return (img);
}
