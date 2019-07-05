/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:52:37 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/05/01 15:43:15 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_live(t_vm *vm, t_process *process)
{
	t_champion	*champ;
	int			id;

	process->pc = (process->pc + 1) % MEM_SIZE;
	id = cw_get_int(vm->vm, (process->pc + process->entrypoint) % MEM_SIZE, 4);
	process->pc = (process->pc + 4) % MEM_SIZE;
	if (DEBUG)
		ft_printf("P    %d | live: %d\n", process->id, id);
	if (!(champ = cw_find_player(&(vm->setting), id)))
		ft_printf("Live failed : no player found for id %d\n", id);
	else
	{
		ft_printf("Player %s (%d) has been reported alive.\n", champ->name, id);
		vm->loop.last_live.index = id;
		vm->loop.last_live.cycle = vm->cycle;
	}
	process->live += 1;
	vm->loop.nb_live += 1;
	return (1);
}
