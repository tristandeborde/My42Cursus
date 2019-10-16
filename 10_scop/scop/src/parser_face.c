/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_face.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:31:35 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/08 12:32:04 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_parser.h"

static int	pushface(t_obj *obj, char **tab, int index)
{
	int		*face;
	t_list	*elem;

	if (NULL == (face = getface(tab, index)))
		return (-1);
	if (NULL == (elem = ft_lstnew(face, sizeof(int) * 9)))
	{
		free(face);
		return (-1);
	}
	free(face);
	ft_list_pushback(&(obj->face), elem);
	return (0);
}

static void	buildpairs(size_t pos, char **tab, char **tmp)
{
	size_t	len;

	len = ft_tablen(tab);
	tmp[0] = tab[0];
	tmp[1] = tab[pos];
	pos = pos + 1 == len ? 1 : pos + 1;
	tmp[2] = tab[pos];
	pos = pos + 1 == len ? 1 : pos + 1;
	tmp[3] = tab[pos];
	tmp[4] = NULL;
}

static int	faceindex(void)
{
	static int	i = 0;

	i = (i + 1) % 6;
	return (i);
}

int			addface(t_obj *obj, char **tab)
{
	char	*tmp[5];
	size_t	i;
	int		index;

	index = faceindex();
	ft_bzero(tmp, sizeof(tmp));
	if (4 != ft_tablen(tab))
	{
		i = 1;
		while ((int)i < (int)ft_tablen(tab))
		{
			buildpairs(i, tab, tmp);
			if (-1 == pushface(obj, tmp, index))
				return (-1);
			++i;
		}
	}
	if (-1 == pushface(obj, tab, index))
		return (-1);
	return (0);
}
