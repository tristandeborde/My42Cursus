/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 12:30:55 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/27 18:08:15 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_process_process(t_vm *vm, int cycle)
{
	t_list *curr;

	curr = vm->process;
	while (curr)
	{
		if (((t_process*)curr->content)->next_cycle == cycle - 1)
			cw_wait_process(vm, curr->content);
		if (((t_process*)curr->content)->next_cycle == cycle)
			cw_exec_process(vm, curr->content);
		curr = curr->next;
	}
}

void	cw_exec_process(t_vm *vm, t_process *process)
{
	t_op	op;
	int		opcode;
	int		i;

	opcode = process->next_opcode;
	if (opcode < 1 || opcode > 16)
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
	}
	else
	{
		i = 0;
		while (g_op_tab[i].opcode != opcode)
			i++;
		op = g_op_tab[i];
		op.f(vm, process);
	}
}

void	cw_wait_process(t_vm *vm, t_process *process)
{
	int		opcode;
	int		i;

	opcode = vm->vm[(process->pc + process->entrypoint) % MEM_SIZE];
	if (opcode < 1 || opcode > 16)
	{
		process->next_cycle += 1;
	}
	else
	{
		i = 0;
		while (g_op_tab[i].opcode != opcode)
			i++;
		process->next_cycle += g_op_tab[i].nb_cycle;
	}
	process->next_opcode = opcode;
}
