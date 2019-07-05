/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:28:42 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 16:24:58 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dark_mole.h"

void	output_nodes(t_list *list)
{
	t_node	*node;

	while (list)
	{
		node = list->content;
		if (node->status == 1)
			ft_putendl("##start");
		if (node->status == 2)
			ft_putendl("##end");
		ft_putnbr(node->id);
		ft_putstr(" ");
		ft_putnbr(node->x);
		ft_putstr(" ");
		ft_putnbr(node->y);
		ft_putstr("\n");
		list = list->next;
	}
}

void	output_tnls(t_list *list)
{
	t_tnl	*tnl;

	while (list)
	{
		tnl = list->content;
		ft_putnbr(tnl->id1);
		ft_putstr("-");
		ft_putnbr(tnl->id2);
		ft_putstr("\n");
		list = list->next;
	}
}

t_mlx	btn_output_map(t_mlx mlx)
{
	ft_putnbr(mlx.cnf.nb_ant);
	ft_putstr("\n");
	output_nodes(mlx.cnf.node);
	output_tnls(mlx.cnf.tnl);
	ft_putendl("END OF OUTPUT !");
	ft_putendl("");
	mlx.cnf.nb_ant = 0;
	mlx.cnf = cnf_reset_tnls(mlx.cnf);
	mlx.cnf = cnf_reset_nodes(mlx.cnf);
	dm_destroy_buttons(&(mlx.cnf));
	mlx_destroy_window(&mlx, mlx.win);
	exit(1);
	return (mlx);
}
