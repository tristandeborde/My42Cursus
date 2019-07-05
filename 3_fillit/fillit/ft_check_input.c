/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:51:55 by tdeborde          #+#    #+#             */
/*   Updated: 2017/12/06 11:42:41 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "fillit.h"
#include "libft.h"

/*
** Ce fichier contient les fonctions de vérification de la validité d'un
** fichier de tetriminos. Si le tetrimino est valide, il est enregistre sous
** forme d'un ushort.
*/

/*
** Cette fonction analyse les caracteres composant le fichier d'input.
** Si c'est un '\n', il doit etre a la fin d'une ligne ou a la fin de grille.
** Si le caractere est un '#', elle convertit sa position (valide) en binaire,
** en l'ecrivant dans un ushort "mask".
*/

extern void		ft_display_usage(void)
{
	ft_putendl("usage : ./fillit source_file");
}

static int		ft_process_hash(int i, char *buf, unsigned short **hash,\
		int *hc)
{
	unsigned short	mask;

	if (*hc == 0)
	{
		if (!(*hash = (unsigned short *)ft_memalloc(sizeof(unsigned short))))
			return (0);
	}
	mask = 1;
	i = i % 21;
	if ((i != 0 && (i + 1) % 5 == 0 && *buf != '\n') ||
		(i == 20 && *buf != '\n' && *buf != -1) ||
		((i + 1) % 5 != 0 && i != 20 &&
			*buf != '.' && *buf != '#'))
		return (0);
	else if (*buf == '#')
	{
		mask = mask << (16 - (((i % 5) + (((i / 5) % 4) * 4))) - 1);
		**hash = **hash + mask;
		(*hc)++;
	}
	return (1);
}

/*
** Cette fonction verifie si les hashtags sont bien adjacents.
*/

static int		ft_check_tetri(char *buf, int i, int nb)
{
	t_pos	neg;
	t_pos	pos;

	neg.x = (i > 0) ? -1 : 0;
	neg.y = (i > 4) ? -5 : 0;
	pos.x = (i < 18) ? 1 : 0;
	pos.y = (i < 14) ? 5 : 0;
	if (*buf == '#')
	{
		if (*(buf + neg.x) == '#' && neg.x != 0)
			nb++;
		if (*(buf + neg.y) == '#' && neg.y != 0)
			nb++;
		if (*(buf + pos.x) == '#' && pos.x != 0)
			nb++;
		if (*(buf + pos.y) == '#' && pos.y != 0)
			nb++;
	}
	return (nb);
}

/*
** Cette fonction lance la verification : elle itere sur la copie du fichier,
** lance les fonctions d'analyse des caracteres. Si le fichier est valide,
** elle retourne les tetriminos sous forme de liste, avec un ushort en content
** de chaque maillon de la liste. Si fichier pas valide, elle retourne NULL.
*/

static t_list	*ft_read_input(char *buf, t_list *list, int nb)
{
	int				i;
	int				hc;
	unsigned short	*hash;

	i = -1;
	hc = 0;
	while (buf[++i] != '\0' && buf[i] != -1)
	{
		nb = ft_check_tetri(&buf[i], i % 21, nb);
		if ((ft_process_hash(i, &buf[i], &hash, &hc) == 0) || hc > 4
				|| (hc == 4 && nb < 6))
			return (NULL);
		if (hc == 4 && buf[i] == '\n' && ((i + 2) % 21 == 0))
		{
			hc = 0;
			nb = 0;
			ft_lstpush_ultimate(&list, (void *)hash, \
					sizeof(unsigned short), &ft_lstpush_back);
		}
	}
	if (((buf[i] == '\0' || buf[i] == -1) && buf[i - 2] == '\n')
			|| i + 1 != (ft_lstsize(list) * 21))
		return (NULL);
	return (list);
}

/*
** Cette fonction copie l'argument passé à argv dans une string.
** Si le fichier fait plus de 547 caractères, soit + de 26 tetriminos,
** elle retourne 0.
*/

extern int		ft_check_input(char **av, t_list **list)
{
	char		*buf;
	int			ret;
	int			fd;
	int			nb;

	nb = 0;
	if (!(buf = ft_strnew(547)))
		return (0);
	else
	{
		fd = open(av[1], O_RDONLY);
		ret = read(fd, (void *)buf, BUF_SIZE);
		if (ret >= 0 && ret < 546)
		{
			if (!(*list = ft_read_input(buf, *list, nb)))
			{
				return (0);
			}
		}
		else
			return (0);
	}
	return (1);
}
