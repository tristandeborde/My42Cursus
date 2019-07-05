/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_tools1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:59 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/25 17:00:06 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		ft_pile_is_sorted(t_piles *piles, char pile, int median)
{
	t_link	*iter;
	t_link	*start;
	int		len;

	len = pile == 'a' ? piles->len_a : piles->len_b;
	if (len < 2)
		return (1);
	iter = pile == 'a' ? piles->start_a : piles->start_b;
	start = iter;
	if (iter->ix != iter->next->ix + 1 && iter->ix <= median
			&& iter->next->ix != 0)
		return (0);
	iter = iter->next;
	while (iter->ix != start->ix)
	{
		if (iter->ix != iter->next->ix + 1 && iter->ix <= median
				&& iter->next->ix != 0)
			return (0);
		iter = iter->next;
	}
	return (1);
}

int		ft_pile_is_sorted_ascending(t_piles *piles, char pile, int median)
{
	t_link	*iter;
	int		len;

	len = pile == 'a' ? piles->len_a : piles->len_b;
	if (len < 2)
		return (1);
	iter = pile == 'a' ? piles->start_a : piles->start_b;
	while (--len)
	{
		if (iter->ix != iter->next->ix - 1 && iter->ix <= median)
			return (0);
		iter = iter->next;
	}
	return (1);
}

t_link	*ft_find_max(t_piles *piles, int limit)
{
	t_link	*iter;
	t_link	*max;

	max = NULL;
	iter = piles->start_a;
	if (iter->ix <= limit)
		max = iter;
	iter = piles->start_a->next;
	while (iter != piles->start_a)
	{
		if (!max && iter->ix <= limit)
			max = iter;
		else if (max && max->num < iter->num && iter->ix <= limit)
			max = iter;
		iter = iter->next;
	}
	return (max);
}

void	ft_sort_piles(t_piles *piles)
{
	t_link	*iter;
	t_link	*current_min;
	t_link	*max;
	int		current_ix;

	current_ix = 0;
	max = ft_find_max(piles, 2147483647);
	while (current_ix < piles->len_a)
	{
		current_min = max;
		iter = piles->start_a;
		if (iter->ix < 0 && current_min->num > iter->num)
			current_min = iter;
		iter = iter->next;
		while (iter != piles->start_a)
		{
			while (iter->ix >= 0 && iter != piles->start_a)
				iter = iter->next;
			if (iter->ix < 0 && current_min->num > iter->num)
				current_min = iter;
			if (iter != piles->start_a)
				iter = iter->next;
		}
		current_min->ix = current_ix++;
	}
}

int		ft_quick_path(t_link *link, t_piles *piles, char pile)
{
	t_link	*tmp;
	t_link	*tmp2;
	t_link	*start;
	int		op;

	tmp = link;
	tmp2 = link;
	start = pile == 'a' ? piles->start_a : piles->start_b;
	op = 0;
	while (tmp->ix != start->ix && tmp2->ix != start->ix)
	{
		tmp = tmp->prev;
		tmp2 = tmp2->next;
		op++;
	}
	while (op)
	{
		if (tmp->ix == start->ix)
			pile == 'a' ? ft_ra(piles, 1) : ft_rb(piles, 1);
		else
			pile == 'a' ? ft_rra(piles, 1) : ft_rrb(piles, 1);
		op--;
	}
	return (1);
}
