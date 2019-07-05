/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:56:33 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/14 14:41:24 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lm_sizelst(t_list *list)
{
	int		i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void	lm_output_line(t_list *path, int nb_ant, int n, int size)
{
	int		i;

	i = n + 1;
	path = path->next;
	while (size > 0)
	{
		if (i > 0 && i <= nb_ant)
		{
			ft_putstr("L");
			ft_putnbr(i);
			ft_putstr("-");
			ft_putstr(lm_name_by_node(path));
		}
		path = path->next;
		size--;
		i--;
		if (size > 0 && i > 0 && i < nb_ant)
			ft_putstr(" ");
	}
	ft_putstr("\n");
}

void	lm_output(t_list *path, int nb)
{
	int		size;
	int		i;

	size = lm_sizelst(path) - 1 + nb;
	i = 0;
	while (i < size - 1)
	{
		lm_output_line(path, nb, i, size - nb);
		i++;
	}
}
