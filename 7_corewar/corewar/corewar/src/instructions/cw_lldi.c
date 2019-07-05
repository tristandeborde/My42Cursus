/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:44:13 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/28 15:42:03 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_ocp(int oocp, t_process *process)
{
	int	ocp;

	ocp = (oocp & 0xfc);
	if (ocp != 0x54 && ocp != 0x64 && ocp != 0x74 &&\
			ocp != 0x58 && ocp != 0x68 && ocp != 0x78)
	{
		if (DEBUG)
			ft_printf("lldi: badocp %02x %d\n", oocp, cw_ocp_offset(ocp, 1, 3));
		process->pc = (process->pc + cw_ocp_offset(ocp, 1, 3)) % MEM_SIZE;
		return (0);
	}
	return (ocp);
}

int				cw_lldi_param(t_vm *vm, t_process *process, int param[2],
		int ret[2])
{
	int				i;
	int				off;
	unsigned char	ocp;

	i = -1;
	off = 1;
	if (!(ocp = cw_ocp(vm->vm[(process->pc + process->entrypoint) % MEM_SIZE],
		process)))
		return (0);
	while (++i < 3)
	{
		if (!(ret[i] = cw_read_ocp_short(vm, process, &param[i], ocp)))
			off = ret[i]++;
		else if (off)
			off += ret[i] == 4 ? 2 : ret[i];
		if (off && ret[i] == 1 & i < 2)
			param[i] = cw_get_4(process->registries[param[i] - 1]);
		else if (off && ret[i] == 2)
			param[i] = cw_get_int(vm->vm, (unsigned int)(process->pc +
			process->entrypoint - off + (param[i] % IDX_MOD)) % MEM_SIZE, 4);
		ocp = ocp << 2;
	}
	return (off);
}

int				cw_lldi(t_vm *vm, t_process *process)
{
	int				param[3];
	int				ret[3];
	int				offset;

	process->pc = (process->pc + 1) % MEM_SIZE;
	if ((offset = cw_lldi_param(vm, process, param, ret)))
	{
		cw_memcpy_from_circle(process->registries[param[2] - 1], vm->vm,
			(unsigned int)(process->pc + process->entrypoint + param[0] +
				param[1] - offset) % MEM_SIZE, REG_SIZE);
		process->carry = !param[0] ? 1 : 0;
		if (DEBUG)
			ft_printf("P    %d | lldi: (%d) + (%d) -> r%d\n", process->id,
				param[0], param[1], param[2]);
	}
	process->pc = (process->pc + 1) % MEM_SIZE;
	return (1);
}
