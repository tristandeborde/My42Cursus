/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:39:48 by tdeborde          #+#    #+#             */
/*   Updated: 2019/06/13 12:29:25 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*malloc_engine(size_t size)
{
	t_blk	*blk;
	void	*ptr;

	ptr = NULL;
	if (size + sizeof(t_blk) > size && size > MEDIUM_SIZE)
	{
		if ((blk = alloc_blk(size + sizeof(t_blk))))
		{
			*blk = init_blk(size);
			blk->is_free = 0;
			handle_large(blk);
			ptr = (void *)blk + sizeof(t_blk);
		}
	}
	else if (size + sizeof(t_blk) > size && size > TINY_SIZE)
		ptr = handle_zones(size, MEDIUM_SIZE, 1);
	else if (size + sizeof(t_blk) > size)
		ptr = handle_zones(size, TINY_SIZE, 0);
	return (ptr);
}

int		change_size(t_blk *blk, void *ptr2, size_t size)
{
	size_t	blk_len;
	t_blk	*blk2;

	blk_len = 0;
	blk2 = NULL;
	if (blk->size <= TINY_SIZE)
		blk_len = TINY_SIZE;
	else if (blk->size <= MEDIUM_SIZE)
		blk_len = MEDIUM_SIZE;
	else
		blk_len = blk->size;
	if (size <= blk_len)
	{
		if (ptr2)
		{
			blk2 = (t_blk *)(ptr2 - sizeof(t_blk));
			blk2->is_free = 1;
		}
		blk->size = size;
		blk->is_free = 0;
		return (1);
	}
	return (0);
}

void	handle_large(t_blk *blk)
{
	t_blk	*iter;

	if (g_zones_table[2] == NULL)
		g_zones_table[2] = blk;
	else
	{
		iter = g_zones_table[2];
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = blk;
	}
}

void	safe_memcpy(void *src, void *dest, size_t size1, size_t size2)
{
	size_t		i;

	i = 0;
	while (i < size1 && i < size2)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
}
