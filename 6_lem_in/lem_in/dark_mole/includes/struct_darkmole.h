/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_darkmole.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:48:37 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 16:18:05 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_DARKMOLE_H
# define STRUCT_DARKMOLE_H

# include "libft.h"

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		endian;
	int		size_line;
	int		size_column;
	int		bpp;
}				t_img;

typedef struct	s_btn
{
	int		id;
	char	*label;
	int		status;
	int		type;
	int		ox;
	int		oy;
	int		x;
	int		y;
	int		color1;
	int		color2;
}				t_btn;

typedef struct	s_node
{
	int		id;
	int		x;
	int		y;
	int		z;
	int		status;
}				t_node;

typedef struct	s_tnl
{
	int		id1;
	int		id2;
}				t_tnl;

typedef struct	s_cnf
{
	int		click;
	int		ox;
	int		oy;
	int		sx;
	int		sy;
	int		grid_size;
	int		id;
	int		status;
	int		nb_ant;
	t_list	*btn;
	t_list	*tnl;
	t_list	*node;
}				t_cnf;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_cnf		cnf;
	t_img		img;
}				t_mlx;

typedef struct	s_pos
{
	int		x;
	int		y;
	int		color;
}				t_pos;

typedef struct	s_line
{
	int		dx;
	int		dy;
	int		xi;
	int		yi;
	int		e;
}				t_line;

#endif
