/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:35:15 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/15 12:59:12 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		main(int ac, char **av)
{
	t_piles		*piles;
	t_ops_tab	*o_tab;
	char		**instruc_tab;
	int			i;

	i = -1;
	if (ac < 2)
		exit(EXIT_SUCCESS);
	piles = ft_read_pile(ac, av);
	o_tab = ft_init_ops_tab();
	instruc_tab = ft_get_instructions(o_tab, piles);
	if (instruc_tab)
	{
		ft_execute_instructions(instruc_tab, piles, o_tab);
		ft_free_instruc_tab(instruc_tab);
	}
	if (ft_is_sorted(piles))
		ft_putendl("OK");
	else
		ft_putendl("KO");
	ft_free_piles(piles);
	return (0);
}
