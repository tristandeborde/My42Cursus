/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:35:23 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/29 16:05:02 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# ifndef BUF_SIZE
#  define BUF_SIZE 1024
# endif

# include "libft.h"
# include <stddef.h>

typedef struct		s_pos
{
	int		x;
	int		y;
}					t_pos;

typedef struct		s_cursor
{
	t_pos			cursor;
	int				map_size;
	unsigned int	*map;
}					t_cursor;

typedef struct		s_tetri
{
	int					offset;
	unsigned int		*tetri;
}					t_tetri;

int					ft_check_input(char **av, t_list **list);
int					ft_backtracking(unsigned int map_size, t_list *tetri_list, \
		t_list **first_hash);
int					ft_display_map(t_list *tetris, t_list *coors,\
		int map_size);
void				ft_display_usage(void);
int					ft_offset_tetri(unsigned int *tetri);
void				ft_parser_tetri(t_list *list, t_list **tetris);
int					ft_tetritype(t_list list, unsigned char *tetri);

#endif
