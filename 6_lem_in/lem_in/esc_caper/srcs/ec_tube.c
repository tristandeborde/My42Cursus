/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_tube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:31:38 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/03 19:25:19 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_dos	**ec_get_tube_coor(int len, int r, t_dos os)
{
	t_dos	**dmap;
	t_ang	a;
	t_dos	b;
	int		i;
	int		j;

	i = 0;
	b = stpd(r, 0, 0);
	a = set_ang(0, 0, 0);
	dmap = ec_new_tube_dmap();
	while (i < 4)
	{
		j = 0;
		while (j < 12)
		{
			dmap[i][j] = ec_doff_set(ec_rotate_all(a, b), os);
			a = ec_up_y(a, 30);
			j++;
		}
		os.z += (double)len / 3.0;
		i++;
	}
	return (dmap);
}

t_pos	**ec_pos_tube(t_mlx mlx, int r, t_dos os, t_dos end)
{
	t_pos	**pmap;
	t_dos	**dmap;
	t_dos	d;
	int		i;
	int		j;

	pmap = ec_new_tube_pmap();
	dmap = ec_get_tube_coor((int)ec_vect_len(os, end), r, stpd(0, 0, 0));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 12)
		{
			d = ec_doff_set(ec_rotate_all(ec_rev_euler(os, end),\
						dmap[i][j]), os);
			pmap[i][j] = rot_2d(mlx.cnf, d);
			j++;
		}
		i++;
	}
	ec_destroy_dtube(dmap);
	return (pmap);
}

t_img	line_tube(t_img img, t_pos **pmap, int i, int j)
{
	t_pos	p1;
	t_pos	p2;

	p1 = pmap[i][j];
	if (i < 3)
	{
		p2 = pmap[i + 1][j];
		img = line(img, p1, p2, 0xffffff);
	}
	if (j == 11)
		p2 = pmap[i][0];
	else
		p2 = pmap[i][j + 1];
	img = line(img, p1, p2, 0xffffff);
	return (img);
}

t_img	ec_draw_tube(t_mlx mlx, int r, t_dos os, t_dos end)
{
	t_pos	**pmap;
	int		i;
	int		j;

	pmap = ec_pos_tube(mlx, r, os, end);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 12)
		{
			mlx.img = line_tube(mlx.img, pmap, i, j);
			j++;
		}
		i++;
	}
	ec_destroy_ptube(pmap);
	return (mlx.img);
}
