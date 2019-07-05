/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 13:43:19 by tdeborde          #+#    #+#             */
/*   Updated: 2018/04/26 16:43:15 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cw_lfork(t_vm *vm, t_process *process)
{
	t_list	*new;
	int		param;
	int		old_pc;

	param = cw_get_int(vm->vm, (process->pc + process->entrypoint + 1)
			% MEM_SIZE, 2);
	old_pc = process->pc + process->entrypoint;
	process->pc = (process->pc + 3) % MEM_SIZE;
	if (!(new = ft_lstnew(process, sizeof(t_process))))
		cw_error(ERR_MALLOC);
	((t_process*)new->content)->pc = (unsigned int)(old_pc + param) % MEM_SIZE;
	((t_process*)new->content)->live = process->live;
	((t_process*)new->content)->entrypoint = 0;
	((t_process*)new->content)->id = ++(vm->nb_process);
	ft_lstpushf(&(vm->process), new);
	if (DEBUG)
		ft_printf("P    %d | lfork %d (%d) P %d\n", process->id, param, \
			old_pc + param, vm->nb_process);
	return (1);
}
