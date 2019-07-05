/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_caper.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:13:26 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/20 12:48:38 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESC_CAPER_H
# define ESC_CAPER_H

# include "libft.h"
# include "struct_escaper.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_parse
{
	t_cnf	(*f)(t_cnf cnf, int *status, char **line);
}				t_parse;

/*
** Parse fcts
*/
t_cnf			ec_parse_ants(t_cnf cnf, int *status, char **line);
t_cnf			ec_fetch_ant(t_cnf cnf, int *status, char **line);
t_cnf			ec_parse_links(t_cnf cnf, int *status, char **line);
t_cnf			ec_parse_nodes(t_cnf cnf, int *status, char **line);
t_cnf			ec_fetch_link(t_cnf cnf, int *status, char **line);
t_cnf			ec_extract_node(t_cnf cnf, int *status, char **line);
t_cnf			ec_fetch_node(t_cnf cnf, int *status, char **line);
t_cnf			ec_fetch_cnf(t_cnf cnf, int *status);
t_parse			*ec_getparse(void);
void			ec_destroy_tab(char **tab);
int				ft_strisdig(char *str);
int				ft_strtabsize(char **tab);
int				ec_line_is_com(char *line);
char			*ec_name_by_node(t_list *elem);
int				ec_node_id_by_name(t_cnf cnf, char *name);
t_node			*ec_check_node_name(t_list *list, char *label);
t_ant			*ec_check_ant_id(t_list *list, char *str);
int				ec_cmd_new_id(t_list *list);
int				ec_chk_node_name(char *s, char c);
t_dos			ec_node_dos(t_list *list, int id);
t_cnf			ec_link_pos(t_cnf cnf);

/*
** Init fcts
*/
t_cnf			cnf_init(void);
t_mlx			esc_caper_init(t_cnf cnf);
t_cnf			ec_parser(t_cnf cnf);
void			ec_cnf_destroy(t_cnf *cnf);
void			ec_node_upz_by_id(int id, t_list *list);

/*
** Interaction fcts
*/
int				mouse_on(int button, int x, int y, void *param);
int				mouse(int button, int x, int y, void *param);
int				drag_drop(int x, int y, void *param);
int				refresh(void *param);
int				actions(int key_hook, void *param);

/*
** Set fcts
*/
t_pos			stp(int x, int y);
t_pos			stp3(int x, int y, int z);
t_dos			stpd(int x, int y, int z);
t_ang			set_ang(int ax, int ay, int az);
t_dos			ec_scale_pos(t_dos p, int x);

/*
** Rotate fcts
*/
double			rotate_z(t_ang a, double x, double y, double z);
double			rotate_y(t_ang a, double x, double y, double z);
double			rotate_x(t_ang a, double x, double y, double z);
t_dos			ec_scale_pos(t_dos p, int x);

/*
** Line fcts
*/
t_img			set_img_pxl(t_img img, int x, int y, int color);
t_img			ec_preline(t_img img, t_cnf cnf, t_dos p1, t_dos p2);
t_img			line(t_img img, t_pos p1, t_pos p2, int color);

/*
** Sphere fcts
*/
t_img			ec_draw_sphere(t_mlx mlx, int r, t_dos d);
t_pos			**ec_new_pmap(void);
t_dos			**ec_new_dmap(void);
void			ec_destroy_pmap(t_pos **map);
void			ec_destroy_dmap(t_dos **map);
t_ang			ec_up_x(t_ang a, int ang);
t_ang			ec_up_y(t_ang a, int ang);
t_dos			ec_rotate_all(t_ang a, t_dos b);
t_dos			ec_doff_set(t_dos p1, t_dos p2);

/*
** Tube fcts
*/
t_pos			**ec_new_tube_pmap(void);
void			ec_destroy_ptube(t_pos **pmap);
t_dos			**ec_new_tube_dmap(void);
void			ec_destroy_dtube(t_dos **dmap);
t_img			ec_draw_tube(t_mlx mlx, int r, t_dos os, t_dos end);
t_ang			ec_rev_euler(t_dos p1, t_dos p2);
double			ec_vect_len(t_dos p1, t_dos p2);

/*
** Draw general fcts
*/
t_mlx			ec_data_to_img(t_mlx mlx);
t_img			reset_img(t_img img);
t_pos			rot_2d(t_cnf cnf, t_dos d);
t_mlx			ec_draw_ping(t_mlx mlx, t_dos p1, t_dos p2, int color);
t_mlx			ec_time_update(t_mlx mlx);

/*
** Ping fcts
*/
t_mlx			ec_ping_move(t_mlx mlx);
t_mlx			ec_ping_hold(t_mlx mlx);
t_cnf			ec_delete_current_cmd(t_cnf cnf);
t_mlx			ec_update_timer_status(t_mlx mlx);

/*
** Actions fcts
*/
t_mlx			ec_key_action(int key, t_mlx mlx);
t_mlx			ec_key_sc_plus(t_mlx mlx);
t_mlx			ec_key_sc_moin(t_mlx mlx);
t_mlx			ec_key_rx(t_mlx mlx);
t_mlx			ec_key_ry(t_mlx mlx);
t_mlx			ec_key_rz(t_mlx mlx);
t_mlx			ec_key_rmx(t_mlx mlx);
t_mlx			ec_key_rmy(t_mlx mlx);
t_mlx			ec_key_rmz(t_mlx mlx);

#endif
