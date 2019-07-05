/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instrucs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 10:14:07 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/21 17:27:47 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_pa(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "pa");
	if (piles->len_b >= 1)
	{
		ft_add_toplink(piles, piles->start_b->num, piles->start_b->ix, 'a');
		ft_del_toplink(piles, 'b');
	}
}

void	ft_pb(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "pb");
	if (piles->len_a >= 1)
	{
		ft_add_toplink(piles, piles->start_a->num, piles->start_a->ix, 'b');
		ft_del_toplink(piles, 'a');
	}
}

void	ft_ra(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "ra");
	if (piles->len_a > 1)
	{
		piles->start_a = piles->start_a->next;
		piles->end_a = piles->end_a->next;
	}
}

void	ft_rb(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "rb");
	if (piles->len_b > 1)
	{
		piles->start_b = piles->start_b->next;
		piles->end_b = piles->end_b->next;
	}
}

void	ft_rr(t_piles *piles, int display)
{
	if (display)
		ft_putendl("rr");
	ft_ra(piles, 0);
	ft_rb(piles, 0);
}
