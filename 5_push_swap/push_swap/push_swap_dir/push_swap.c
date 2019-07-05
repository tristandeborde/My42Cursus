/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:59 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/14 14:45:27 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		ft_launch_quicksort(t_piles *piles, int len)
{
	int	pivot;
	int	lim;

	if (len <= 12)
		return (0);
	else if (len <= 41)
		lim = 5;
	else
		lim = 20;
	pivot = len / 2;
	while (pivot > lim)
	{
		ft_quicksort(piles, pivot, len, 'a');
		pivot /= 2;
	}
	pivot *= 2;
	ft_selection_sort_a(piles, 'a', pivot);
	ft_selection_sort_b(piles, pivot * 2 + 1);
	ft_quicksort(piles, pivot * 3 + 1, pivot * 4 + 1, 'b');
	ft_selection_sort_b(piles, pivot * 3 + 1);
	ft_selection_sort_a_end(piles, 'a', pivot * 3, len + 1);
	return (pivot);
}

int		ft_continue_quicksort(t_piles *piles, int pivot, int len)
{
	int new_pivot;
	int tmp_pivot;

	len = piles->len_a;
	new_pivot = len * 2;
	tmp_pivot = len / 2;
	while (new_pivot - len > pivot)
	{
		ft_quicksort(piles, new_pivot, len * 2, 'b');
		new_pivot -= tmp_pivot;
		tmp_pivot /= 2;
	}
	new_pivot += (tmp_pivot * 2);
	ft_selection_sort_b(piles, new_pivot);
	ft_selection_sort_a_end(piles, 'a', new_pivot, new_pivot + pivot);
	ft_quicksort(piles, piles->end_a->ix + pivot, len * 2, 'a');
	ft_selection_sort_a_end(piles, 'a', new_pivot + pivot,
			piles->len_a);
	ft_selection_sort_b(piles, piles->len_a + pivot);
	return (new_pivot);
}

void	ft_sort_small(t_piles *piles, int len)
{
	t_link	*iter;
	t_link	*current_min;

	current_min = NULL;
	while (!ft_pile_is_sorted_ascending(piles, 'a', len + 1))
	{
		iter = piles->start_a;
		if (!iter->ix || (piles->len_b && iter->ix == piles->start_b->ix + 1))
			ft_pb(piles, 1);
		else if (iter->ix > iter->next->ix && iter->ix != len - 1)
			ft_sa(piles, 1);
		else if (iter->ix < iter->prev->ix && iter->prev->ix != len - 1)
			ft_rra(piles, 1);
		else
		{
			current_min = piles->start_a;
			iter = piles->start_a->next;
			ft_find_local_min(iter, &current_min, len, &piles->start_a);
			ft_quick_path(current_min, piles, 'a');
		}
	}
	ft_organize_sorted_piles(piles, current_min);
}

void	ft_sort_very_small(t_piles *piles)
{
	t_link	*iter;

	while (!ft_is_sorted(piles))
	{
		iter = piles->start_a;
		if (iter->ix > iter->next->ix)
			ft_sa(piles, 1);
		else if (iter->ix < iter->prev->ix || !iter->prev->ix)
			ft_rra(piles, 1);
		else
			ft_ra(piles, 1);
	}
}

int		main(int ac, char **av)
{
	t_piles		*piles;
	int			pivot;
	int			len;
	int			len_save;

	if (ac < 2)
		exit(EXIT_SUCCESS);
	piles = ft_read_pile(ac, av);
	len = piles->len_a;
	len_save = len;
	ft_sort_piles(piles);
	if (!(pivot = ft_launch_quicksort(piles, len)))
		len > 3 ? ft_sort_small(piles, len) : ft_sort_very_small(piles);
	else
	{
		while (pivot && piles->len_b > pivot)
			ft_continue_quicksort(piles, pivot, len);
		if (!ft_pile_is_sorted(piles, 'a', len + 1))
			ft_selection_sort_b(piles, len_save + 1);
		if (!ft_is_sorted(piles))
			ft_selection_sort_a(piles, 'a', len_save + 1);
	}
	ft_print_instrucs(piles);
	ft_free_piles(piles);
	return (0);
}
