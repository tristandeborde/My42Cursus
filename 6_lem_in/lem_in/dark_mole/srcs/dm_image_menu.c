/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_image_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:08:45 by cmaxime           #+#    #+#             */
/*   Updated: 2018/02/26 19:23:39 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

t_img	set_menu_img(t_img img)
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
			if (j > 1000)
			{
				color = 0x4c4c4c;
				img = set_img_pxl(img, j, i, color);
			}
			j++;
		}
		i++;
	}
	return (img);
}

t_img	dm_draw_btn(t_img img, t_btn *btn)
{
	int		color;
	int		ox;
	int		oy;
	int		x;
	int		y;

	ox = btn->ox;
	oy = btn->oy;
	x = btn->x;
	y = btn->y;
	if (btn->status != 0 && btn->type > 1)
		color = btn->color2;
	else
		color = btn->color1;
	img = dm_draw_box(img, stp(ox, oy), stp(x, y), color);
	img = dm_draw_box(img, stp(ox + 1, oy + 1), stp(x - 2, y - 2), color);
	img = dm_draw_box(img, stp(ox + 2, oy + 2), stp(x - 4, y - 4), color);
	img = set_img_pxl(img, ox, oy, 0x4c4c4c);
	img = set_img_pxl(img, ox + x, oy, 0x4c4c4c);
	img = set_img_pxl(img, ox, oy + y, 0x4c4c4c);
	img = set_img_pxl(img, ox + x, oy + y, 0x4c4c4c);
	return (img);
}

void	dm_menu_txt(t_mlx *mlx)
{
	t_list	*list;
	t_btn	*btn;
	int		x;
	int		y;

	list = mlx->cnf.btn;
	while (list)
	{
		btn = list->content;
		if (btn->id == 13)
		{
			free(btn->label);
			btn->label = ft_itoa(mlx->cnf.nb_ant);
		}
		x = btn->ox + (btn->x - ft_strlen(btn->label) * 10) / 2;
		y = btn->oy + (btn->y - 20) / 2;
		mlx_string_put(mlx->mlx, mlx->win, x, y, 0xffffff, btn->label);
		list = list->next;
	}
}

t_mlx	dm_draw_menu(t_mlx mlx)
{
	t_list	*list;
	t_btn	*btn;

	mlx.img = set_menu_img(mlx.img);
	list = mlx.cnf.btn;
	while (list)
	{
		btn = list->content;
		if (btn->type != 0)
			mlx.img = dm_draw_btn(mlx.img, btn);
		list = list->next;
	}
	return (mlx);
}
