/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 20:55:04 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/15 12:34:36 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

t_ops_tab	*ft_init_ops_tab(void)
{
	static	t_ops_tab	tab[11] = {
						{"sa", &ft_sa},
						{"sb", &ft_sb},
						{"ss", &ft_ss},
						{"pa", &ft_pa},
						{"pb", &ft_pb},
						{"ra", &ft_ra},
						{"rb", &ft_rb},
						{"rr", &ft_rr},
						{"rra", &ft_rra},
						{"rrb", &ft_rrb},
						{"rrr", &ft_rrr},
						};

	return (tab);
}

t_piles		*ft_init_piles(void)
{
	t_piles *piles;

	if (!(piles = (t_piles *)ft_memalloc(sizeof(t_piles))))
		ft_handle_error();
	piles->len_a = 0;
	piles->len_b = 0;
	piles->start_a = NULL;
	piles->start_b = NULL;
	piles->end_a = NULL;
	piles->end_b = NULL;
	piles->instrucs_start = NULL;
	return (piles);
}
