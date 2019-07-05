/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:35:15 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/15 12:57:30 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free_instruc_tab(char **instruc_tab)
{
	int		i;

	i = -1;
	while (instruc_tab[++i])
		free(instruc_tab[i]);
	free(instruc_tab);
}

int		ft_execute_instructions(char **instruc_tab, t_piles *piles,
		t_ops_tab *o_tab)
{
	int		i;
	int		j;

	i = 0;
	while (instruc_tab[i])
	{
		j = -1;
		while (++j < 11)
		{
			if (!ft_strcmp(o_tab[j].op_name, instruc_tab[i]))
				o_tab[j].op_func(piles, 0);
		}
		i++;
	}
	return (1);
}

int		ft_check_instructions(char *str, t_ops_tab *o_tab)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		if (!ft_strcmp(o_tab[i].op_name, str))
			return (1);
		i++;
	}
	return (0);
}

char	**ft_get_instructions(t_ops_tab *o_tab, t_piles *piles)
{
	char	**instruc_tab;
	char	*str;
	int		i;
	int		ret;

	i = 0;
	instruc_tab = NULL;
	while ((ret = get_next_line(0, &str)) > 0 && ++i)
	{
		if (ret > 1)
		{
			if ((!ft_check_instructions(str, o_tab)
					&& !(ret == 1 && *str == 0)) || !ft_strlen(str))
				ft_stop_reading_instrucs(str, instruc_tab, piles);
			if (i > 1)
				instruc_tab = ft_strtab_add(instruc_tab, i);
			else if (!(instruc_tab = (char **)ft_memalloc(sizeof(char *) * 2)))
				ft_handle_error();
			instruc_tab[i - 1] = ft_strdup(str);
			instruc_tab[i] = 0;
		}
		free(str);
	}
	free(str);
	return (instruc_tab);
}

t_piles	*ft_read_pile(int ac, char **av)
{
	t_piles		*piles;
	intmax_t	num;
	int			i;
	int			j;
	char		***tab;

	piles = ft_init_piles();
	tab = ft_get_pile_tab(ac, av);
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (tab[i][++j])
		{
			if (!ft_check_params(tab[i], j, &num, piles))
			{
				ft_free_piles(piles);
				ft_free_input_tab(tab, ac);
				ft_handle_error();
			}
			ft_add_endlink(piles, num, -1, 'a');
		}
	}
	ft_free_input_tab(tab, ac);
	return (piles);
}
