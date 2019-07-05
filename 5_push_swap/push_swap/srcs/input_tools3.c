/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:48:15 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/15 12:30:37 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		ft_check_int(intmax_t nb)
{
	if (nb > INT_MAX || nb < INT_MIN)
		return (0);
	return (1);
}

int		ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**ft_strtab_add(char **strtab, int len)
{
	char	**new_strtab;
	int		i;

	i = -1;
	if (!(new_strtab = (char **)ft_memalloc(sizeof(char *) * (len + 1))))
		ft_handle_error();
	while (++i < len - 1)
		new_strtab[i] = strtab[i];
	free(strtab);
	return (new_strtab);
}

int		ft_is_sorted(t_piles *piles)
{
	int		i;
	t_link	*iter;

	i = 1;
	if (piles->len_b)
		return (0);
	iter = piles->start_a;
	while (i < piles->len_a)
	{
		if (iter->num > iter->next->num)
			return (0);
		iter = iter->next;
		i++;
	}
	return (1);
}

int		ft_check_dups(t_piles *piles, intmax_t num)
{
	int		i;
	t_link	*iter;

	i = 0;
	iter = piles->start_a;
	while (iter && i < piles->len_a)
	{
		if (num == iter->num)
			return (0);
		iter = iter->next;
		i++;
	}
	return (1);
}
