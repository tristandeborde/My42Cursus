/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instrucs3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:02:01 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/22 16:02:25 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rra(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "rra");
	if (piles->len_a > 1)
	{
		piles->start_a = piles->start_a->prev;
		piles->end_a = piles->end_a->prev;
	}
}

void	ft_rrb(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "rrb");
	if (piles->len_b > 1)
	{
		piles->start_b = piles->start_b->prev;
		piles->end_b = piles->end_b->prev;
	}
}

void	ft_rrr(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "rrr");
	ft_rra(piles, 0);
	ft_rrb(piles, 0);
}
