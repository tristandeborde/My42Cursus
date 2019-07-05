/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instrucs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 10:14:07 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/22 15:29:23 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(t_piles *piles, char pile)
{
	t_link	**start;
	t_link	**end;
	int		len;

	start = pile == 'a' ? &piles->start_a : &piles->start_b;
	end = pile == 'a' ? &piles->end_a : &piles->end_b;
	len = pile == 'a' ? piles->len_a : piles->len_b;
	if (len == 2)
	{
		(*end) = (*start);
		(*start) = (*start)->next;
	}
	else
	{
		(*start) = (*start)->next;
		(*start)->prev->next = (*start)->next;
		(*start)->next->prev = (*start)->prev;
		(*start)->prev = (*end);
		(*end)->next->prev = (*start);
		(*start)->next = (*end)->next;
		(*end)->next = (*start);
	}
}

void	ft_sa(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "sa");
	if (piles->len_a >= 2)
		ft_swap(piles, 'a');
}

void	ft_sb(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "sb");
	if (piles->len_b >= 2)
		ft_swap(piles, 'b');
}

void	ft_ss(t_piles *piles, int display)
{
	if (display)
		ft_add_instruc(piles, "ss");
	if (piles->len_a >= 2)
		ft_swap(piles, 'a');
	if (piles->len_b >= 2)
		ft_swap(piles, 'b');
}
