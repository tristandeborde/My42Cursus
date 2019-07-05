/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 14:05:22 by tdeborde          #+#    #+#             */
/*   Updated: 2019/06/13 13:52:03 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int			print_blk_mem(t_blk *blk)
{
	void	*ptr;

	ptr = (void *)blk;
	if (blk->is_free)
		return (0);
	ft_puthex((uintptr_t)(ptr + sizeof(t_blk)));
	write(1, " - ", 3);
	ft_puthex((uintptr_t)(ptr + sizeof(t_blk) + blk->size));
	write(1, " : ", 3);
	ft_putunbr(blk->size);
	write(1, " octets\n", 8);
	return (blk->size);
}

void		print_zone_mem(void *ptr, int i)
{
	if (ptr == (void *)UINTPTR_MAX)
		return ;
	if (i == 0)
		write(1, "TINY : ", 7);
	else if (i == 1)
		write(1, "SMALL : ", 8);
	else
		write(1, "LARGE : ", 8);
	ft_puthex((uintptr_t)ptr);
	write(1, "\n", 1);
}

void		*find_min(void *last, int *ix)
{
	int			i;
	size_t		count;
	size_t		size;
	void		*iter;
	void		*min;

	i = 0;
	iter = NULL;
	min = (void *)UINTPTR_MAX;
	while (i < 3)
	{
		iter = (void *)g_zones_table[i];
		while (iter)
		{
			if (iter < min && iter > last && iter)
				min = iter;
			*ix = min == iter ? i : *ix;
			size = i == 0 ? TINY_SIZE : MEDIUM_SIZE;
			count = i == 2 ? 1 : BLK_NUMBER;
			iter += (count - 1) * (size + sizeof(t_blk));
			iter = (void *)(((t_blk *)iter)->next);
		}
		i++;
	}
	return (min);
}

void		write_total(unsigned long long total)
{
	write(1, "Total : ", 8);
	ft_putunbr(total);
	write(1, " octets\n", 8);
}

void		show_alloc_mem(void)
{
	int					ix;
	size_t				size;
	unsigned long long	total;
	void				*min;
	void				*last;

	pthread_mutex_lock(&g_mutex);
	total = 0;
	size = 0;
	min = NULL;
	last = NULL;
	while (last != (void *)UINTPTR_MAX)
	{
		min = find_min(last, &ix);
		last = min;
		print_zone_mem(min, ix);
		size = ix != 2 ? BLK_NUMBER : 2;
		while (min != (void *)UINTPTR_MAX && --size > 0)
		{
			total += print_blk_mem(min);
			min = (void *)(((t_blk *)min)->next);
		}
	}
	write_total(total);
	pthread_mutex_unlock(&g_mutex);
}
