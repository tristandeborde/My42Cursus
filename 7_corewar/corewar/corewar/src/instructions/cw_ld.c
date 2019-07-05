/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:43:44 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/28 15:42:37 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_ocp(int ocp, t_process *process)
{
	if ((ocp & 0xf0) != 0xd0 && (ocp & 0xf0) != 0x90)
	{
		if (DEBUG)
			ft_printf("P    %d | ld: bad ocp %02x %d\n", \
				process->id, ocp, cw_ocp_offset(ocp, 0, 2));
		process->pc = (process->pc + cw_ocp_offset(ocp, 0, 2)) % MEM_SIZE;
		return (0);
	}
	return (ocp);
}

int				cw_ld_param(t_vm *vm, t_process *process, int param[2],
		int ret[2])
{
	int				i;
	int				off;
	unsigned char	ocp;

	i = -1;
	off = 1;
	if (!(ocp = cw_ocp(vm->vm[(process->pc + process->entrypoint) % MEM_SIZE],\
		process)))
		return (0);
	while (++i < 2)
	{
		if (!(ret[i] = cw_read_ocp(vm, process, &param[i], ocp)))
			off = ret[i]++;
		else if (off)
			off += ret[i];
		if (off && ret[i] == 2)
			param[i] = cw_get_int(vm->vm, (unsigned int)(process->pc +
			process->entrypoint - off + (param[i] % IDX_MOD)) % MEM_SIZE, 4);
		ocp = ocp << 2;
	}
	return (off);
}

int				cw_ld(t_vm *vm, t_process *process)
{
	int				param[2];
	int				ret[2];

	process->pc = (process->pc + 1) % MEM_SIZE;
	if ((cw_ld_param(vm, process, param, ret)))
	{
		cw_rev_get(process->registries[param[1] - 1], param[0]);
		process->carry = !param[0] ? 1 : 0;
		if (DEBUG)
			ft_printf("P    %d | ld %d r%d\n", process->id, param[0], param[1]);
	}
	process->pc = (process->pc + 1) % MEM_SIZE;
	return (1);
}
