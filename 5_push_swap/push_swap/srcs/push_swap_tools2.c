/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:59 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/06 17:18:09 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_find_local_min(t_link *iter, t_link **current_min, int median,
		t_link **start)
{
	while (iter->ix <= median && iter->ix != (*start)->ix)
	{
		if ((*current_min)->num > iter->num)
			(*current_min) = iter;
		iter = iter->next;
	}
}

static void	ft_find_local_max(t_link *iter, t_link **current_max, int lim,
		int median)
{
	static int	count;

	count = 0;
	while (iter->ix > median && iter->ix <= lim)
	{
		if ((*current_max)->ix < iter->ix)
			(*current_max) = iter;
		iter = !(count % 2) ? iter->next : iter->prev;
	}
	count++;
}

int			ft_selection_sort_a_end(t_piles *piles, char pile, int median,
		int lim)
{
	t_link	*iter;
	t_link	*current_max;

	if (ft_is_sorted(piles))
		return (0);
	while (ft_has_median_a(piles, median, 'a', lim))
	{
		iter = piles->start_a->next;
		current_max = ft_find_max(piles, lim);
		ft_find_local_max(iter, &current_max, lim, median);
		iter = piles->start_a->prev;
		ft_find_local_max(iter, &current_max, lim, median);
		ft_quick_path(current_max, piles, pile);
		ft_pb(piles, 1);
	}
	if (piles->start_a->ix == piles->end_a->ix + 1)
		ft_ra(piles, 1);
	while (piles->start_b->ix == piles->start_b->next->ix - 1)
	{
		ft_pa(piles, 1);
		ft_ra(piles, 1);
	}
	ft_pa(piles, 1);
	ft_ra(piles, 1);
	return (1);
}

int			ft_selection_sort_b(t_piles *piles, int median)
{
	t_link	*iter;
	t_link	*current_min;

	if (ft_is_sorted(piles))
		return (0);
	while (piles->len_b > 1 && ft_has_median_b1(piles, median))
	{
		current_min = piles->start_b;
		iter = piles->start_b->next;
		ft_find_local_min(iter, &current_min, 2147483647, &piles->start_b);
		ft_quick_path(current_min, piles, 'b');
		ft_pa(piles, 1);
		ft_ra(piles, 1);
	}
	while (piles->len_b && piles->end_a->ix == piles->start_b->ix - 1)
	{
		ft_pa(piles, 1);
		ft_ra(piles, 1);
	}
	return (1);
}

int			ft_selection_sort_a(t_piles *piles, char pile, int median)
{
	t_link	*iter;
	t_link	*current_min;
	t_link	*start1;

	if (ft_is_sorted(piles))
		return (0);
	start1 = pile == 'a' ? piles->start_a : piles->start_b;
	while (!ft_pile_is_sorted(piles, pile, median))
	{
		iter = pile == 'a' ? piles->start_a->next : piles->start_b->next;
		current_min = pile == 'a' ? piles->start_a : piles->start_b;
		while (iter->ix <= median && iter != piles->start_a)
		{
			if (current_min->num > iter->num)
				current_min = iter;
			iter = iter->next;
		}
		ft_quick_path(current_min, piles, pile);
		ft_pb(piles, 1);
	}
	while (piles->start_a->ix == piles->start_b->ix + 1)
		ft_pa(piles, 1);
	return (1);
}
