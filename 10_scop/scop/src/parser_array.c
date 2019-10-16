/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:00:12 by cmaxime           #+#    #+#             */
/*   Updated: 2019/09/30 19:40:48 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_parser.h"

float		*getvector(char **tab, size_t len)
{
	size_t	i;
	float	*vect;

	if ((int)(len + 1) != ft_tablen(tab))
		return (NULL);
	if (NULL == (vect = (float*)ft_memalloc(sizeof(float) * len)))
		return (NULL);
	i = 0;
	while (++i < len + 1)
	{
		if (-1 == ft_isfloat(tab[i]))
		{
			free(vect);
			return (NULL);
		}
		vect[i - 1] = (float)ft_atof(tab[i]);
	}
	return (vect);
}

static int	facefill(int *face, char **tmp, int index)
{
	size_t	i;

	if (1 == ft_tablen(tmp))
	{
		if (-1 == ft_isint(tmp[0]))
			return (-1);
		face[0] = ft_atoi(tmp[0]);
		face[2] = index;
		return (0);
	}
	if (3 != ft_tablen(tmp))
		return (-1);
	i = 0;
	while (i < 3)
	{
		if (-1 == ft_isint(tmp[i]))
			return (-1);
		face[i] = ft_atoi(tmp[i]);
		++i;
	}
	face[2] = index;
	return (0);
}

int			*getface(char **tab, int index)
{
	size_t	i;
	int		*face;
	char	**tmp;

	if (4 != ft_tablen(tab))
		return (NULL);
	if (NULL == (face = (int*)ft_memalloc(sizeof(int) * 9)))
		return (NULL);
	i = 0;
	while (++i < 4)
	{
		tmp = ft_strsplit(tab[i], '/');
		if (-1 == facefill(face + (i - 1) * 3, tmp, index))
		{
			ft_deltab(tmp);
			free(face);
			return (NULL);
		}
		ft_deltab(tmp);
	}
	return (face);
}
