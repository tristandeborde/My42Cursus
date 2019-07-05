/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_tetri.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:49:35 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/29 16:33:09 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

/*
** Ce fichier contient l'ensemble des fonction permettant de transformer une
** list de tetrimino donné sous la d'une suite binaire contenu dans un
** unsigned short, en une matrice binaire du même type que la map.
*/

extern int			ft_offset_tetri(unsigned int *tetri)
{
	unsigned int	mask;
	unsigned int	offset;
	int				i;

	mask = 0;
	offset = 0;
	i = 0;
	while (tetri[i] != 0 && mask != 15)
	{
		mask = 15;
		mask = tetri[i] & mask;
		if (mask > offset)
			offset = mask;
		i++;
	}
	i = 0;
	while (offset)
	{
		offset = offset >> 1;
		i++;
	}
	return (i);
}

/*
** Cette fonction est la segond étape du résultat obtenu grace à la
** fonction ft_parsing. Ici on eleve tout les premiere coloned n'étant
** composé que de zero.
*/

static unsigned int	*ft_sanitalize_tetri2(unsigned int *tmp)
{
	unsigned int	mask;
	int				i;
	int				j;

	mask = 1;
	i = 0;
	while (tmp[i] != 0)
	{
		mask = mask & tmp[i];
		if (mask == 1)
			break ;
		i++;
		if (tmp[i] == 0 && mask == 0)
		{
			j = 0;
			while (tmp[j] != 0)
			{
				tmp[j] = tmp[j] >> 1;
				j++;
			}
			i = 0;
		}
		mask = 1;
	}
	return (tmp);
}

/*
** C'est la premiere etape de netoyage du résultats obtenu grace à la
** fonction ft_parsing. Ici on enleve tout les premiere ligne de la matrice qui
** aurai une valeur égale à zero.
*/

static unsigned int	*ft_sanitalize_tetri1(unsigned int *tetri)
{
	unsigned int	*tmp;
	int				i;
	int				j;

	tmp = tetri;
	i = 0;
	while (tmp[i] == 0)
		i++;
	j = i;
	while (tmp[i] != 0)
	{
		ft_swap_uint((tmp + (i - j)), (tmp + i));
		i++;
	}
	tmp = ft_sanitalize_tetri2(tmp);
	return (tmp);
}

/*
** Cette fonction  effectue l'allocation de la matrice de taille 5 et
** positione l'integralité des bit fort du tetrimio (short) dans la matrice
*/

static t_list		*ft_parsing(t_list *list, t_list *tetris)
{
	unsigned int	*tetri;
	unsigned short	*tmp;
	int				i;
	t_tetri			tetrioff;

	if (!(tetri = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 5)))
		return (NULL);
	tetri[5] = 0;
	tmp = (unsigned short *)list->content;
	i = 0;
	while (i < 4)
	{
		tetri[i] = 0;
		tetri[i] = (unsigned int)(*tmp << (32 - (16 - ((i * 4)))));
		tetri[i] = (tetri[i] >> 28);
		i++;
	}
	tetrioff.tetri = tetri;
	tetrioff.offset = 0;
	ft_lstpush_ultimate(&tetris, (int *)&tetrioff, sizeof(t_tetri) * 5, \
			&ft_lstpush_back);
	return (tetris);
}

/*
** Cette fonction est la fonction appelé pour effectuer le parsing des
** tetrimino (short) en une matric d'int, elle se déroule en 2 étapes. Fase de
** création de la matrice et fase de netoyage de celle ci.
*/

extern void			ft_parser_tetri(t_list *list, t_list **tetris)
{
	t_list	*tmp;
	t_tetri	*tmp_tetri;

	tmp = list;
	while (tmp)
	{
		*tetris = ft_parsing(tmp, *tetris);
		tmp = tmp->next;
	}
	tmp = *tetris;
	while (tmp)
	{
		tmp_tetri = (t_tetri *)(tmp->content);
		tmp_tetri->tetri = ft_sanitalize_tetri1(tmp_tetri->tetri);
		tmp_tetri->offset = ft_offset_tetri(tmp_tetri->tetri);
		tmp->content = (void *)tmp_tetri;
		tmp = tmp->next;
	}
}
