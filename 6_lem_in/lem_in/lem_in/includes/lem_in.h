/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 12:08:12 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/20 12:51:03 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "struct_lem_in.h"
# include "libft.h"
# include <limits.h>

# define L(x) ft_putendl_fd(x, 1)
# define S(x) ft_putstr_fd(x, 1)
# define N(x) ft_putnbr_fd(x, 1)
# define C(x) ft_putchar_fd(x, 1)
# define ND(x, y) N(x); S(" - "); N(y); L("")

/*
** Parsing ftcs
*/
t_data		lm_fetch_data(t_data data);
t_data		lm_parse_ants(t_data data, int *status, char **line);
t_data		lm_fetch_ant(t_data data, int *status, char **line);
t_data		lm_parse_nodes(t_data data, int *status, char **line);
t_data		lm_fetch_node(t_data data, int *status, char **line);
t_data		lm_extract_node(t_data data, int *status, char **line);
int			lm_line_is_status(char *line);
t_data		lm_parse_links(t_data data, int *status, char **line);
t_data		lm_fetch_link(t_data data, int *status, char **line);
t_data		lm_extract_link(t_data data, t_list *elem1, t_list *elem2);

/*
** Parsing gnrl fcts
*/
int			lm_line_is_com(char	*line);
int			ft_strtabsize(char **tab);
int			ft_strisdig(char *str);
void		lm_destroy_tab(char **tab);
t_parse		*lm_getparse(void);

/*
** Node data interaction
*/
char		*lm_name_by_node(t_list *elem);
t_list		*lm_node_by_name(t_data data, char *name);
t_list		*lm_get_end_node(t_list *list);

/*
** Pathfinding fcts
*/
t_list		*lm_find_one_path(t_data *data);
void		lm_launch_path(t_data *data);

/*
** Checking fcts
*/
int			lm_check_data(t_data *data);
void		lm_link_vals_fill(t_data *data);

/*
** Output fcts
*/
void		lm_output(t_list *path, int nb);

/*
** Free fcts
*/
void		lm_destroy_data(t_data data);
void		lm_destroy_node(t_list *node);
void		lm_destroy_link(t_list *link);

#endif
