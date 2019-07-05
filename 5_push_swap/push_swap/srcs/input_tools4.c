/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:53:03 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/15 12:32:53 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free_piles(t_piles *piles)
{
	t_link	*iter;
	t_link	*iter2;
	int		i;

	iter = piles->start_a;
	iter2 = iter;
	i = -1;
	while (++i < piles->len_a)
	{
		iter2 = iter;
		iter = iter->next;
		free(iter2);
	}
	iter = piles->start_b;
	iter2 = iter;
	i = -1;
	while (++i < piles->len_b)
	{
		iter2 = iter;
		iter = iter->next;
		free(iter2);
	}
	free(piles);
}

void	ft_stop_reading_instrucs(char *str, char **instruc_tab, t_piles *piles)
{
	free(str);
	if (instruc_tab)
		ft_free_instruc_tab(instruc_tab);
	ft_handle_error();
	ft_free_piles(piles);
}

void	ft_free_input_tab(char ***tab, int ac)
{
	int		i;
	int		j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (tab[i][++j])
			free(tab[i][j]);
		free(tab[i]);
	}
	free(tab);
}

char	***ft_get_pile_tab(int ac, char **av)
{
	int		i;
	char	***tab;

	i = 0;
	if (!(tab = (char ***)ft_memalloc(sizeof(char **) * ac)))
		ft_handle_error();
	while (++i < ac)
		tab[i] = ft_strsplit(av[i], ' ');
	return (tab);
}

int		ft_check_params(char **tab, int j, intmax_t *num, t_piles *piles)
{
	if (!ft_isnumber(tab[j])
		|| !ft_check_int((*num = ft_atoi_base(tab[j], 10)))
		|| !ft_check_dups(piles, *num = ft_atoi_base(tab[j], 10)))
		return (0);
	return (1);
}
