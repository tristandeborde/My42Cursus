/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_mole.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:47:24 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 16:33:55 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

t_list	*init_buttons(void)
{
	t_list	*list;

	list = NULL;
	list = dm_add_button(list, "Dark Mole", 0, 20);
	list = dm_add_button(list, "Menu", 0, 20);
	list = dm_add_button(list, "Size of map", 0, 20);
	list = dm_add_button(list, "-", 1, 25);
	list = dm_add_button(list, "+", 1, 25);
	list = dm_add_button(list, "add elements", 0, 20);
	list = dm_add_button(list, "Node", 2, 25);
	list = dm_add_button(list, "Link", 2, 25);
	list = dm_add_button(list, "type of node", 0, 20);
	list = dm_add_button(list, "Start", 3, 25);
	list = dm_add_button(list, "End", 3, 25);
	list = dm_add_button(list, "Ants", 0, 10);
	list = dm_add_button(list, "", 0, 10);
	list = dm_add_button(list, "+", 1, 25);
	list = dm_add_button(list, "-", 1, 25);
	list = dm_add_button(list, "", 0, 100);
	list = dm_add_button(list, "Reset", 1, 25);
	list = dm_add_button(list, "Output", 1, 25);
	return (list);
}

t_cnf	cnf_init(void)
{
	t_cnf		cnf;
	t_list		*elem;

	elem = init_buttons();
	cnf.grid_size = 10;
	cnf.id = 0;
	cnf.ox = 0;
	cnf.oy = 0;
	cnf.sx = 0;
	cnf.sy = 0;
	cnf.status = 0;
	cnf.nb_ant = 0;
	cnf.btn = elem;
	cnf.tnl = NULL;
	cnf.click = 0;
	cnf.node = NULL;
	return (cnf);
}

t_mlx	dark_mole_init(t_cnf cnf)
{
	t_mlx	mlx;
	size_t	size_x;
	size_t	size_y;

	size_x = 1200;
	size_y = 1000;
	mlx.mlx = mlx_init();
	mlx.cnf = cnf;
	mlx.img.size_column = size_y;
	mlx.win = mlx_new_window(mlx.mlx, size_x, size_y, "dark-mole");
	mlx.img.img = mlx_new_image(mlx.mlx, size_x, size_y);
	mlx.img.data = (int*)mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, \
			&mlx.img.size_line, &mlx.img.endian);
	return (mlx);
}

int		main(void)
{
	t_mlx	mlx;
	t_cnf	cnf;

	cnf = cnf_init();
	mlx = dark_mole_init(cnf);
	mlx = dm_draw_menu(mlx);
	mlx = dm_data_to_img(mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	dm_menu_txt(&mlx);
	mlx_hook(mlx.win, 2, (1L << 0), actions, &mlx);
	mlx_hook(mlx.win, 4, (1L << 3), mouse_on, &mlx);
	mlx_hook(mlx.win, 5, (1L << 3), mouse, &mlx);
	mlx_hook(mlx.win, 6, (1L << 2), drag_drop, &mlx);
	mlx_loop_hook(mlx.mlx, refresh, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
