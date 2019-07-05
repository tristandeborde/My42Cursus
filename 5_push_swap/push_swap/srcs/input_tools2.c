/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:48:15 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/05 15:16:38 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_handle_error(void)
{
	ft_putendl("Error");
	exit(EXIT_FAILURE);
}

void	ft_print_links(t_link *link1, t_link *link2)
{
	char	*ix;
	char	*num;

	num = link1 ? ft_itoa_base(link1->num, 10) : NULL;
	ix = link1 ? ft_itoa_base(link1->ix, 10) : NULL;
	if (num)
		ft_printf("num:%s\t/\tix:%s\t|", num, ix);
	else
		ft_putstr("\t\t\t|");
	num = link2 ? ft_itoa_base(link2->num, 10) : NULL;
	ix = link2 ? ft_itoa_base(link2->ix, 10) : NULL;
	if (num)
		ft_printf("\tnum:%s /  ix:%s", num, ix);
	ft_putstr("\n");
}

void	ft_print_tab(t_piles *piles)
{
	int		len;
	int		len_a;
	int		len_b;
	t_link	*link1;
	t_link	*link2;

	link1 = piles->start_a;
	link2 = piles->start_b;
	len = piles->len_a > piles->len_b ? piles->len_a : piles->len_b;
	len_a = piles->len_a;
	len_b = piles->len_b;
	while (len)
	{
		ft_print_links(link1, link2);
		len_a--;
		len_b--;
		link1 = len_a > 0 ? link1->next : NULL;
		link2 = len_b > 0 ? link2->next : NULL;
		len--;
	}
}

void	ft_print_piles(t_piles *piles)
{
	ft_putendl("###Pile A:###\t\t|\t ###Pile B:###");
	ft_print_tab(piles);
	ft_putendl("---------------------------------------");
	ft_putendl("- start:\t\t|\t\t\t");
	ft_print_links(piles->start_a, piles->start_b);
	ft_putendl("- end:\t\t\t|\t\t\t");
	ft_print_links(piles->end_a, piles->end_b);
	ft_putendl("\n=================================================\n");
}
