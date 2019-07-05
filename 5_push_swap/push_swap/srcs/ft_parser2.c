/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:29:29 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/14 12:29:16 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		ft_print_instrucs(t_piles *piles)
{
	t_instrucs	*iter;

	if (!(iter = piles->instrucs_start))
		return (0);
	ft_optimize_instrucs(piles);
	while (iter)
	{
		ft_putendl(iter->buff);
		iter = iter->next;
	}
	ft_free_instrucs(piles);
	return (1);
}
