/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:43:51 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/27 17:46:46 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_ocp(int oocp, t_process *process)
{
	int	ocp;

	ocp = (oocp & 0xfc);
	if (ocp != 0x54 && ocp != 0xd4 && ocp != 0x94 &&\
			ocp != 0x64 && ocp != 0xe4 && ocp != 0xa4)
	{
		if (DEBUG)
			ft_printf("ldi: bad ocp %02x\n", oocp);
		process->pc = (process->pc + cw_ocp_offset(ocp, 1, 3)) % MEM_SIZE;
		return (0);
	}
	return (ocp);
}

int				cw_ldi_param(t_vm *vm, t_process *process, int param[2],
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
		if (off && ret[i] == 1 && i < 2)
			param[i] = cw_get_4(process->registries[param[i] - 1]);
		else if (off && ret[i] == 2)
			param[i] = cw_get_int(vm->vm, (unsigned int)(process->pc +
			process->entrypoint - off + (param[i] % IDX_MOD)) % MEM_SIZE, 4);
		ocp = ocp << 2;
	}
	return (off);
}

int				cw_ldi(t_vm *vm, t_process *process)
{
	int				param[3];
	int				ret[3];
	int				offset;

	process->pc = (process->pc + 1) % MEM_SIZE;
	if ((offset = cw_ldi_param(vm, process, param, ret)))
	{
		cw_memcpy_from_circle(process->registries[param[2] - 1], vm->vm,
			(unsigned int)(process->pc + process->entrypoint + ((param[0]
				+ param[1]) % IDX_MOD) - offset) % MEM_SIZE, REG_SIZE);
		if (DEBUG)
		{
			ft_printf("P    %d | ldi %d %d r%d\n", process->id, param[0],
					param[1], param[2]);
			ft_printf("       | load from %d + %d = %d (with pc and mod %d)\n",
				param[0], param[1], param[0] + param[1], param[0]
				+ param[1] + process->pc - offset);
		}
	}
	process->pc = (process->pc + 1) % MEM_SIZE;
	return (1);
}
