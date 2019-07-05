/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_image_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:06:54 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 17:49:07 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

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
			color = 0;
			img = set_img_pxl(img, j, i, color);
			j++;
		}
		i++;
	}
	return (img);
}

t_img	ec_preline(t_img img, t_cnf cnf, t_dos p1, t_dos p2)
{
	t_pos	p_1;
	t_pos	p_2;

	p_1 = rot_2d(cnf, p1);
	p_2 = rot_2d(cnf, p2);
	img = line(img, p_1, p_2, 0xffffff);
	return (img);
}

t_img	ec_image_node(t_mlx mlx)
{
	t_list	*list;
	t_node	*node;
	t_dos	p;

	list = mlx.cnf.node;
	while (list)
	{
		node = list->content;
		p = ec_scale_pos(stpd(node->x, node->y, node->z), 10);
		mlx.img = ec_draw_sphere(mlx, 2, p);
		list = list->next;
	}
	return (mlx.img);
}

t_img	ec_image_link(t_mlx mlx)
{
	t_list	*list;
	t_link	*link;
	t_dos	p1;
	t_dos	p2;

	list = mlx.cnf.link;
	while (list)
	{
		link = list->content;
		p1 = ec_scale_pos(link->p1, 10);
		p2 = ec_scale_pos(link->p2, 10);
		mlx.img = ec_preline(mlx.img, mlx.cnf, p1, p2);
		list = list->next;
	}
	return (mlx.img);
}

t_mlx	ec_data_to_img(t_mlx mlx)
{
	mlx.img = reset_img(mlx.img);
	mlx.img = ec_image_node(mlx);
	mlx.img = ec_image_link(mlx);
	return (mlx);
}
