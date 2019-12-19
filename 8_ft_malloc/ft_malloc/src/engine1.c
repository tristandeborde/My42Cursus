/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 14:07:29 by tdeborde          #+#    #+#             */
/*   Updated: 2019/06/05 13:46:55 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_blk		*find_ptr(void *ptr)
{
	int		i;
	void	*real_mem;
	t_blk	*blk;

	i = 0;
	while (i < 3)
	{
		blk = g_zones_table[i];
		while (blk)
		{
			real_mem = (void *)(blk) + sizeof(t_blk);
			if (real_mem == ptr)
				return (blk);
			blk = blk->next;
		}
		i++;
	}
	return (NULL);
}

t_blk		init_blk(size_t size)
{
	t_blk	blk;

	blk.size = size;
	blk.next = NULL;
	blk.is_free = 1;
	return (blk);
}

t_blk		*alloc_blk(size_t size)
{
	t_blk				*blk;

	if ((size) % getpagesize())
		size += getpagesize() - (size % getpagesize());
	if ((blk = (t_blk *)mmap(0, size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		write(2, "Could not mmap page size into memory.\n", 38);
		return (NULL);
	}
	return (blk);
}

t_blk		*create_zone(size_t real_size, size_t size, t_blk *prev, int id)
{
	size_t				total_size;
	t_blk				*blk;
	void				*ptr;
	void				*first;

	total_size = BLK_NUMBER * (size + sizeof(t_blk));
	if (!(ptr = (void *)alloc_blk(total_size)))
		return (NULL);
	first = ptr;
	while (ptr < (first + total_size))
	{
		blk = (t_blk *)ptr;
		*blk = init_blk(size);
		ptr += (size + sizeof(t_blk));
		blk->next = ptr < (first + total_size) ? (t_blk *)ptr : NULL;
	}
	if (prev == NULL)
		g_zones_table[id] = (t_blk *)first;
	else
		prev->next = (t_blk *)first;
	blk = (t_blk *)(first);
	blk->is_free = 0;
	blk->size = real_size;
	first += (sizeof(t_blk));
	return (first);
}

void		*handle_zones(size_t real_size, size_t size, int id)
{
	void	*ptr;
	t_blk	*blk;
	t_blk	*prev;

	blk = g_zones_table[id];
	prev = blk;
	while (blk != NULL)
	{
		if (blk->is_free)
		{
			blk->size = real_size;
			blk->is_free = 0;
			ptr = (void *)blk + sizeof(t_blk);
			return (ptr);
		}
		prev = blk;
		blk = blk->next;
	}
	return (create_zone(real_size, size, prev, id));
}
