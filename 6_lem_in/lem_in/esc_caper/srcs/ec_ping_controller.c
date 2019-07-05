/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ec_ping_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:30:05 by cmaxime           #+#    #+#             */
/*   Updated: 2018/03/05 18:32:38 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "esc_caper.h"

t_mlx	ec_ping_move(t_mlx mlx)
{
	int		id;
	t_list	*list;
	t_cmd	*cmd;
	t_dos	p;

	list = mlx.cnf.cmd;
	if (list)
	{
		cmd = list->content;
		id = cmd->id;
		while (list && cmd->id == id)
		{
			p = ec_scale_pos(stpd(cmd->dst->x, cmd->dst->y,\
					cmd->dst->y), 10);
			mlx = ec_draw_ping(mlx, p, \
					ec_scale_pos(cmd->ant->pos, 10), 16);
			list = list->next;
			if (list)
				cmd = list->content;
		}
	}
	return (mlx);
}

t_mlx	ec_ping_hold(t_mlx mlx)
{
	t_list	*list;
	t_ant	*ant;
	t_dos	p;

	list = mlx.cnf.ant;
	while (list)
	{
		ant = list->content;
		p = ec_scale_pos(ant->pos, 10);
		mlx = ec_draw_ping(mlx, p, p, 8);
		list = list->next;
	}
	return (mlx);
}

t_cnf	ec_delete_current_cmd(t_cnf cnf)
{
	t_cmd	*cmd;
	t_list	*list;
	t_list	*buff;
	int		id;
	t_dos	p;

	list = cnf.cmd;
	if (list)
	{
		cmd = list->content;
		id = cmd->id;
		while (list && cmd->id == id)
		{
			p = stpd(cmd->dst->x, cmd->dst->y, cmd->dst->z);
			cmd->ant->pos = p;
			buff = list->next;
			free(list->content);
			free(list);
			list = buff;
			if (list)
				cmd = list->content;
		}
	}
	cnf.cmd = list;
	return (cnf);
}

t_mlx	ec_update_timer_status(t_mlx mlx)
{
	mlx.cnf.ant_sts = (mlx.cnf.ant_sts + 1) % 2;
	if (mlx.cnf.cmd == NULL)
		mlx.cnf.ant_sts = 1;
	if (mlx.cnf.ant_sts == 1)
		mlx.cnf = ec_delete_current_cmd(mlx.cnf);
	return (mlx);
}
