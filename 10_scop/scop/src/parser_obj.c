/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:58:03 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/08 12:29:35 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_parser.h"

static void		get_index_max(t_obj *obj, int *index)
{
	t_list	*elem;
	int		i;
	int		j;

	elem = obj->face;
	ft_bzero(index, sizeof(int) * 3);
	while (elem)
	{
		i = -1;
		while (++i < 3)
		{
			j = -1;
			while (++j < 3)
			{
				index[i] = index[i] < ((int*)(elem->content))[j * 3 + i] ?
					((int*)(elem->content))[j * 3 + i] : index[i];
			}
		}
		elem = elem->next;
	}
}

static int		is_corrupted(t_obj *obj)
{
	int		tab[3];

	get_index_max(obj, tab);
	if (tab[0] > ft_lstlen(obj->vertex)
			|| tab[1] > ft_lstlen(obj->normal))
		return (-1);
	return (0);
}

static float	*getcolor(int index)
{
	static float colors[6][3] = {
		{0.15f, 0.15f, 0.15f},
		{0.33f, 0.33f, 0.33f},
		{0.50f, 0.50f, 0.50f},
		{0.66f, 0.66f, 0.66f},
		{0.75f, 0.75f, 0.75f},
		{0.99f, 0.99f, 0.99f},
	};

	if (index < 0 || index > (int)sizeof(colors) - 1)
		return (colors[0]);
	return (colors[index]);
}

static size_t	pack_data(int *index, t_obj *obj, float *vertices, size_t i)
{
	int		j;
	float	*tmp;

	j = 0;
	while (j < 3)
	{
		tmp = (float*)ft_lstgetcontent(obj->vertex,
				(size_t)index[j * 3] - 1);
		vertices[i * 8] = tmp[0];
		vertices[i * 8 + 1] = tmp[1];
		vertices[i * 8 + 2] = tmp[2];
		tmp = (float*)ft_lstgetcontent(obj->normal,
				(size_t)index[j * 3 + 1] - 1);
		vertices[i * 8 + 3] = tmp[0];
		vertices[i * 8 + 4] = tmp[1];
		tmp = getcolor(index[j * 3 + 2]);
		vertices[i * 8 + 5] = tmp[0];
		vertices[i * 8 + 6] = tmp[1];
		vertices[i * 8 + 7] = tmp[2];
		++j;
		++i;
	}
	return (i);
}

int				compile(t_obj *obj, float **vertices, size_t *len)
{
	t_list	*elem;
	size_t	i;

	if (-1 == is_corrupted(obj))
		return (-1);
	elem = obj->face;
	*len = 3 * 8 * (size_t)ft_lstlen(elem);
	if (NULL == (*vertices = (float*)ft_memalloc(sizeof(float)
					* (*len))))
		return (-1);
	i = 0;
	while (elem)
	{
		i = pack_data((int*)(elem->content), obj, *vertices, i);
		elem = elem->next;
	}
	return (0);
}
