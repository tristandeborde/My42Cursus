/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_tetris.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:36:42 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/30 10:55:31 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"
#include <stdlib.h>

static int		ft_delete_tetri(t_tetri *tetri, t_cursor *cursor)
{
	int tmp;
	int y;

	tmp = cursor->cursor.x - tetri->offset;
	y = cursor->cursor.y;
	cursor->map[y] &= ~(tetri->tetri[0] << tmp);
	cursor->map[y + 1] &= ~(tetri->tetri[1] << tmp);
	cursor->map[y + 2] &= ~(tetri->tetri[2] << tmp);
	cursor->map[y + 3] &= ~(tetri->tetri[3] << tmp);
	return (1);
}

/*
** Cette fonction checke si un tetri peut etre place aux coordonnes passees en
** parametre dans t_cursor. Pour cela, elle s'appelle en backtracking : si tous
** les hashtags suivants sont placables, elle ecrit  le tetri sur la map. Sinon
** elle renvoie 0.
*/

static int		ft_place_next_hashes(t_tetri *tetri, t_cursor cursor, \
		int index, t_pos *first_coor)
{
	int				y;
	unsigned int	line;

	if (!(line = tetri->tetri[index] << (cursor.cursor.x - tetri->offset)))
		return (1);
	y = cursor.cursor.y;
	if (y >= cursor.map_size)
		return (0);
	if (!(line & cursor.map[cursor.cursor.y]))
	{
		(cursor.cursor.y)++;
		if (ft_place_next_hashes(tetri, cursor, ++index, first_coor))
		{
			cursor.map[y] += line;
			cursor.cursor.y = y;
			first_coor->x = cursor.map_size - cursor.cursor.x;
			first_coor->y = cursor.cursor.y;
			return (1);
		}
	}
	return (0);
}

/*
** Cette fonction itere sur chacune des cases de la map en partant de la
** premiere en haut a gauche. A chaque case, elle appelle ft_place_next_hashes
** pour voir si le tetri peut etre place. Si il est placable, elle retourne 1
** sinon elle continue a iterer
*/

static int		ft_find_empty_space(t_tetri *tetri, t_cursor *cursor, \
		t_pos *first_coor)
{
	while (cursor->cursor.y < cursor->map_size)
	{
		while (cursor->cursor.x >= tetri->offset)
		{
			if (ft_place_next_hashes(tetri, *cursor, 0, first_coor) != 0)
				return (1);
			(cursor->cursor.x)--;
		}
		(cursor->cursor.x) = cursor->map_size;
		(cursor->cursor.y)++;
	}
	return (0);
}

/*
** Cette fonction itere sur une liste de tetri, et essaie de les placer sur la
** map. Si le tetri est placable, elle se rappelle avec le tetri suivant. Si
** elle n'arrive pas a placer un tetri, elle change le tetri precedent de
** position et reessaie de placer les suivant.
*/

static int		ft_place_tetris(t_list *tetri_list, t_cursor *cursor, \
		int tetri_nb, t_list **first_hash)
{
	t_cursor		tmp;
	t_pos			first_coor;
	t_tetri			*tetri;

	if (!(tetri_list))
		return (1);
	tetri = (t_tetri *)tetri_list->content;
	tmp = *cursor;
	while (ft_find_empty_space(tetri, &tmp, &first_coor))
	{
		if (ft_place_tetris(tetri_list->next, cursor, ++tetri_nb, first_hash))
		{
			ft_lstpush_ultimate(first_hash, (void *)&first_coor, \
					sizeof(t_pos), &ft_lstpush_front);
			return (1);
		}
		ft_delete_tetri(tetri, &tmp);
		if (tmp.cursor.x < tetri->offset)
		{
			tmp.cursor.x = tmp.map_size + 1;
			tmp.cursor.y++;
		}
		tmp.cursor.x--;
	}
	return (0);
}

/*
** Cette fonction genere un tableau d'uint de taille map_size. Elle appelle
** ensuite les fonctions ci-dessus pour placer sur ce tableau tous les tetris
** de tetri_list. Si les tetris sont tous placables, elle renvoie 1. Sinon,
** elle se rappelle elle-meme en augmentant la taille du tableau de 1.
*/

extern int		ft_backtracking(unsigned int map_size, t_list *tetri_list, \
		t_list **first_hash)
{
	t_cursor		cursor;

	if (!(cursor.map = \
				(unsigned int *)ft_memalloc(sizeof(unsigned int) * map_size))
			|| map_size == 32)
		return (0);
	cursor.cursor.x = map_size;
	cursor.cursor.y = 0;
	cursor.map_size = map_size;
	if (ft_place_tetris(tetri_list, &cursor, 0, first_hash))
		return (cursor.map_size);
	else
	{
		free(cursor.map);
		return (ft_backtracking(cursor.map_size + 1, tetri_list, first_hash));
	}
}
