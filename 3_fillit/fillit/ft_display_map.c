/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 18:11:41 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/29 14:37:46 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

static char		*ft_strnew_dots(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if ((str = (char *)(ft_memalloc(sizeof(char) * size + 1))) == 0)
		return (0);
	while (i < size)
	{
		str[i++] = '.';
	}
	str[i] = '\0';
	return (str);
}

static void		ft_write_tetri(unsigned int *tetri, t_pos *coors, char **map,
		int tetri_num)
{
	int				i;
	int				x;
	unsigned int	offset_bit;
	unsigned int	tmp;

	offset_bit = 1 << (ft_offset_tetri(tetri) - 1);
	i = 0;
	while (tetri[i])
	{
		x = coors->x;
		tmp = offset_bit;
		while (tmp > 0)
		{
			if (tetri[i] & tmp)
				map[coors->y + i][x] = tetri_num + 65;
			tmp = tmp >> 1;
			x++;
		}
		i++;
	}
}

static void		ft_iter_tetris(t_list *tetris, t_list *coors, char **map)
{
	int				tetri_num;
	t_pos			*pos_tetri;
	t_tetri			*tmp_tetri;
	unsigned int	*tetri;

	tetri_num = 0;
	while (coors)
	{
		pos_tetri = (t_pos *)coors->content;
		tmp_tetri = (t_tetri *)(tetris->content);
		tetri = (unsigned int*)tmp_tetri->tetri;
		ft_write_tetri(tetri, pos_tetri, map, tetri_num);
		tetris = tetris->next;
		coors = coors->next;
		tetri_num++;
	}
}

extern int		ft_display_map(t_list *tetris, t_list *coors, int map_size)
{
	int		i;
	char	**map;

	(void)tetris;
	(void)coors;
	if (!(map = (char **)ft_memalloc(sizeof(char *) * map_size)))
		return (0);
	i = 0;
	map[map_size] = NULL;
	while (i < map_size)
		map[i++] = ft_strnew_dots(map_size);
	ft_iter_tetris(tetris, coors, map);
	i = 0;
	while (i < map_size)
		ft_putendl(map[i++]);
	return (1);
}
