/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_escaper.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:44:47 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 17:07:44 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ESCAPER_H
# define STRUCT_ESCAPER_H

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

typedef struct	s_dos
{
	double	x;
	double	y;
	double	z;
}				t_dos;

typedef struct	s_pos
{
	int		x;
	int		y;
	int		z;
}				t_pos;

typedef struct	s_cnf
{
	int		ant_sts;
	int		time;
	int		click;
	int		ox;
	int		oy;
	int		sx;
	int		sy;
	int		ax;
	int		ay;
	int		az;
	double	scale;
	int		buff;
	t_list	*node;
	t_list	*link;
	t_list	*ant;
	t_list	*cmd;
}				t_cnf;

typedef struct	s_node
{
	int		id;
	char	*label;
	int		x;
	int		y;
	int		z;
	int		status;
}				t_node;

typedef struct	s_link
{
	int		id1;
	int		id2;
	t_dos	p1;
	t_dos	p2;
}				t_link;

typedef struct	s_ant
{
	int		id;
	int		id_pos;
	t_dos	pos;
	int		id_dst;
}				t_ant;

typedef struct	s_cmd
{
	int		id;
	t_ant	*ant;
	t_node	*dst;
}				t_cmd;

typedef struct	s_ang
{
	double	x;
	double	y;
	double	z;
}				t_ang;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_cnf		cnf;
	t_img		img;
}				t_mlx;

typedef struct	s_line
{
	int		dx;
	int		dy;
	int		xi;
	int		yi;
	int		e;
}				t_line;

#endif
