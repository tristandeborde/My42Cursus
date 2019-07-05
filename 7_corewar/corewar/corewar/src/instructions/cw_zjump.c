/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_zjump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:08:22 by tdeborde          #+#    #+#             */
/*   Updated: 2018/04/28 15:38:25 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			cw_zjump(t_vm *vm, t_process *process)
{
	short		param;

	param = 0;
	if (process->carry)
	{
		param = cw_get_int(vm->vm, (process->pc + process->entrypoint + 1) \
			% MEM_SIZE, 2);
		process->pc = (unsigned int)(process->pc + \
			(short)param % IDX_MOD) % MEM_SIZE;
	}
	else
		process->pc = (process->pc + 3) % MEM_SIZE;
	if (DEBUG)
		ft_printf("P    %d | zjump: %d %s\n", process->id, param, \
			process->carry ? "OK" : "KO");
	return (1);
}
