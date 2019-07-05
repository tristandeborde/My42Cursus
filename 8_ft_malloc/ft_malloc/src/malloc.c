/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:20:20 by tdeborde          #+#    #+#             */
/*   Updated: 2019/07/03 17:22:54 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_blk				*g_zones_table[3] = {NULL};
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

void		free(void *ptr)
{
	t_blk	*blk;

	pthread_mutex_lock(&g_mutex);
	blk = NULL;
	if (ptr != NULL && (blk = check_ptr(ptr)))
		blk->is_free = 1;
	pthread_mutex_unlock(&g_mutex);
}

void		*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = NULL;
	while (size == 0 || size % 16)
		size++;
	ptr = malloc_engine(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
	size_t	i;
	t_blk	*blk;
	void	*ptr2;

	pthread_mutex_lock(&g_mutex);
	i = 0;
	blk = NULL;
	ptr2 = (!check_ptr(ptr) && ptr) ? NULL : malloc_engine(size);
	if (ptr2 && ptr && check_ptr(ptr))
	{
		blk = (t_blk *)(ptr - sizeof(t_blk));
		blk->is_free = 1;
		if (change_size(blk, ptr2, size))
			ptr2 = ptr;
		else
		{
			while (i < size && i < blk->size)
			{
				((char *)ptr2)[i] = ((char *)ptr)[i];
				i++;
			}
		}
	}
	pthread_mutex_unlock(&g_mutex);
	return (ptr2);
}

void		*calloc(size_t n, size_t size)
{
	size_t	i;
	size_t	total;
	void	*p;

	pthread_mutex_lock(&g_mutex);
	i = 0;
	p = NULL;
	if ((total = n * size) / size == n)
		p = malloc_engine(total);
	if (p)
	{
		while (i < total)
		{
			((char *)p)[i] = 0;
			i++;
		}
	}
	pthread_mutex_unlock(&g_mutex);
	return (p);
}
