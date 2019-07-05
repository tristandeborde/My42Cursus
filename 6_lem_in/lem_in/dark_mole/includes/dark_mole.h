/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_mole.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:44:34 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 16:32:31 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DARK_MOLE_H
# define DARK_MOLE_H

# include "libft.h"
# include "struct_darkmole.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

/*
** Update fcts
*/
t_mlx			dm_data_to_img(t_mlx mlx);
t_mlx			dm_init_img(t_mlx mlx);
t_mlx			dm_draw_menu(t_mlx mlx);
t_img			set_menu_img(t_img img);
void			dm_menu_txt(t_mlx *mlx);

/*
** Draw fcts
*/
t_img			reset_img(t_img img);
t_img			set_img_pxl(t_img img, int x, int y, int color);
t_img			line(t_img img, t_pos p1, t_pos p2, int color);
t_img			circle(t_img img, t_pos p, int radius, int color);
t_pos			stp(int x, int y);
t_img			dm_draw_box(t_img img, t_pos p1, t_pos p2, int color);
t_mlx			dm_draw_tnls(t_mlx mlx);
t_mlx			dm_draw_nodes(t_mlx mlx);

/*
** MLX fcts
*/
t_mlx			dark_mole_init(t_cnf cnf);
int				refresh(void *param);
int				actions(int key_hook, void *param);
int				drag_drop(int x, int y, void *param);
int				mouse(int button, int x, int y, void *param);
int				mouse_on(int button, int x, int y, void *param);
int				dm_find_button(t_mlx *mlx, int y);
void			dm_destroy_buttons(t_cnf *cnf);
t_list			*dm_add_button(t_list *list, char *name, int type, int size);
t_mlx			dm_reset_btn(t_mlx mlx);
int				dm_clicked_btn(t_mlx mlx);

/*
** Node fcts
*/
int				dm_node_oxy(t_mlx mlx, int xi, int mod);
int				cnf_node_id_by_pos(t_list *list, int x, int y);
t_list			*cnf_add_node(t_mlx mlx, t_list *list, int x, int y);
int				dm_check_node_pos(t_list *list, int x, int y);
int				dm_node_fresh_id(t_list *list);
t_cnf			cnf_reset_nodes(t_cnf cnf);
t_list			*dm_free_node_id(t_list *elem, int id);

/*
** Tnl fcts
*/
int				dm_check_tnl_ids(t_list *list, int id1, int id2);
t_list			*cnf_add_tnl(t_list *list, int id1, int id2);
t_cnf			cnf_add_link(t_mlx mlx, t_cnf cnf, int x, int y);
t_cnf			cnf_reset_tnls(t_cnf cnf);
t_list			*dm_free_tnl_ids(t_list *elem, int id1, int id2);
t_mlx			dm_free_bad_tnl(t_mlx mlx);

/*
** Action fcts
*/
t_mlx			dm_key_action(int n, t_mlx mlx);
t_mlx			scale_up(t_mlx mlx);
t_mlx			scale_down(t_mlx mlx);
t_mlx			btn_add_node(t_mlx mlx);
t_mlx			btn_add_tnl(t_mlx mlx);
t_mlx			btn_add_start(t_mlx mlx);
t_mlx			btn_add_end(t_mlx mlx);
t_mlx			cnf_add_map(t_mlx mlx, int x, int y);
t_mlx			btn_reset_map(t_mlx mlx);
t_mlx			btn_ant_up(t_mlx mlx);
t_mlx			btn_ant_down(t_mlx mlx);
t_mlx			btn_output_map(t_mlx mlx);

#endif
