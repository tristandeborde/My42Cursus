/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_op_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:43:20 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/26 15:16:51 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_rev_get(unsigned char *registries, int nb)
{
	registries[0] = (unsigned char)((nb >> 24) & 0xff);
	registries[1] = (unsigned char)((nb >> 16) & 0xff);
	registries[2] = (unsigned char)((nb >> 8) & 0xff);
	registries[3] = (unsigned char)((nb) & 0xff);
}

int			cw_read_ocp(t_vm *vm, t_process *process, int *param,
		unsigned char ocp_trunc)
{
	if ((ocp_trunc & 128) && (ocp_trunc & 64))
	{
		*param = cw_get_int(vm->vm, (process->pc + process->entrypoint + 1)
				% MEM_SIZE, 2);
		process->pc = (process->pc + 2) % MEM_SIZE;
		*param = (short)*param;
		return (2);
	}
	else if ((ocp_trunc & 128))
	{
		*param = cw_get_int(vm->vm, (process->pc + process->entrypoint + 1)
				% MEM_SIZE, 4);
		process->pc = (process->pc + 4) % MEM_SIZE;
		return (4);
	}
	else
	{
		*param = cw_get_1(&(vm->vm[(process->pc + process->entrypoint + 1)
					% MEM_SIZE]));
		process->pc = (process->pc + 1) % MEM_SIZE;
		if (param && !cw_check_reg(*param))
			return (0);
		return (1);
	}
}

int			cw_read_ocp_short(t_vm *vm, t_process *process, int *param,
		unsigned char ocp_trunc)
{
	if (ocp_trunc & 128)
	{
		*param = cw_get_int(vm->vm, (process->pc + process->entrypoint + 1)
				% MEM_SIZE, 2);
		process->pc = (process->pc + 2) % MEM_SIZE;
		*param = (short)*param;
		if (ocp_trunc & 64)
			return (2);
		return (4);
	}
	else
	{
		*param = cw_get_1(&(vm->vm[(process->pc + process->entrypoint + 1)
					% MEM_SIZE]));
		process->pc = (process->pc + 1) % MEM_SIZE;
		if (param && !cw_check_reg(*param))
			return (0);
		return (1);
	}
}

int			cw_ocp_offset(unsigned char ocp_trunc, int is_short, int nb)
{
	int		offset;
	int		count;

	offset = 0;
	count = 0;
	ft_printf("%#04x\n", ocp_trunc);
	while (count < nb)
	{
		if ((ocp_trunc & 0b10000000) && (ocp_trunc & 0b01000000))
			offset += 2;
		else if ((ocp_trunc & 0b10000000))
			offset += is_short ? 2 : 4;
		else if (ocp_trunc & 0b01000000)
			offset += 1;
		count++;
		ocp_trunc = ocp_trunc << 2;
	}
	return (offset);
}
