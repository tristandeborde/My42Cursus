/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:44:50 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/28 15:38:54 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_ocp(int oocp, t_process *process)
{
	int	ocp;

	ocp = (oocp & 0xfc);
	if (ocp != 0x54 && ocp != 0xd4 && ocp != 0x74 &&\
		ocp != 0xf4 && ocp != 0x94 && ocp != 0x64 &&\
		ocp != 0xb4 && ocp != 0xe4 && ocp != 0xa4)
	{
		if (DEBUG)
			ft_printf("xor: bad ocp %02x\n", oocp);
		process->pc = (process->pc + cw_ocp_offset(ocp, 0, 3)) % MEM_SIZE;
		return (0);
	}
	return (ocp);
}

int				cw_xor_param(t_vm *vm, t_process *process, int param[3],
		int ret[3])
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
		if (!(ret[i] = cw_read_ocp(vm, process, &param[i], ocp)))
			off = ret[i]++;
		else if (off)
			off += ret[i];
		if (off && ret[i] == 1 && i < 2)
			param[i] = cw_get_4(process->registries[param[i] - 1]);
		else if (off && ret[i] == 2)
			param[i] = cw_get_int(vm->vm, (unsigned int)(process->pc + \
			process->entrypoint - off + (param[i] % IDX_MOD)) % MEM_SIZE, 4);
		ocp = ocp << 2;
	}
	return (off);
}

int				cw_xor(t_vm *vm, t_process *process)
{
	int				param[3];
	int				ret[3];

	process->pc = (process->pc + 1) % MEM_SIZE;
	if ((cw_xor_param(vm, process, param, ret)))
	{
		cw_rev_get(process->registries[param[2] - 1], (param[0] ^ param[1]));
		process->carry = !(param[0] ^ param[1]) ? 1 : 0;
		if (DEBUG)
			ft_printf("P    %d | xor: %d ^ %d (%d) -> r%d\n", \
				process->id, param[0], param[1], param[0] ^ param[1], param[2]);
	}
	process->pc = (process->pc + 1) % MEM_SIZE;
	return (1);
}
