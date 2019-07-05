/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_tools3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:59 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/25 16:58:24 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		ft_has_median_a(t_piles *piles, int median, char pile, int limit)
{
	t_link	*iter;
	t_link	*start;

	iter = pile == 'a' ? piles->start_a : piles->start_b;
	start = iter;
	if (iter->ix >= median && iter->ix < limit)
		return (1);
	iter = iter->next;
	while (iter != start)
	{
		if (iter->ix >= median && iter->ix < limit)
			return (1);
		iter = iter->next;
	}
	return (0);
}

int		ft_has_median_b1(t_piles *piles, int median)
{
	t_link	*iter;

	iter = piles->start_b;
	if (iter->ix <= median)
		return (1);
	iter = iter->next;
	while (iter != piles->start_b)
	{
		if (iter->ix <= median)
			return (1);
		iter = iter->next;
	}
	return (0);
}

void	ft_organize_sorted_piles(t_piles *piles, t_link *current_min)
{
	t_link	*iter;
	int		i;

	i = -1;
	iter = piles->start_a;
	while (++i < piles->len_a)
	{
		if (iter->ix > iter->next->ix)
			current_min = iter->next;
		iter = iter->next;
	}
	ft_quick_path(current_min, piles, 'a');
	while (piles->len_b)
		ft_pa(piles, 1);
}

int		ft_quicksort(t_piles *piles, int pivot, int lim, char pile)
{
	t_link	*iter;

	if (ft_is_sorted(piles))
		return (0);
	iter = pile == 'a' ? piles->start_a : piles->start_b;
	while (ft_has_median_a(piles, pivot, pile, lim))
	{
		if (iter->ix >= pivot && iter->ix < lim)
		{
			ft_quick_path(iter, piles, pile);
			pile == 'a' ? ft_pb(piles, 1) : ft_pa(piles, 1);
			iter = pile == 'a' ? piles->start_a : piles->start_b;
		}
		else
			iter = iter->next;
	}
	return (pivot);
}
