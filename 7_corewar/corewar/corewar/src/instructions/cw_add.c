/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:43:37 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/28 15:42:22 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_ocp(int ocp, t_process *process)
{
	if ((ocp & 0xfc) != 0x54)
	{
		if (DEBUG)
			ft_printf("add: bad ocp %02x\n", ocp);
		process->pc = (process->pc + cw_ocp_offset(ocp, 0, 3)) % MEM_SIZE;
		return (0);
	}
	return (ocp);
}

int				cw_add_param(t_vm *vm, t_process *process, int param[3],
		int ret[3])
{
	int				i;
	int				check;
	unsigned char	ocp;

	i = -1;
	check = 1;
	if (!(ocp = cw_ocp(vm->vm[(process->pc + process->entrypoint) % MEM_SIZE], \
		process)))
		return (0);
	while (++i < 3)
	{
		if (!(ret[i] = cw_read_ocp(vm, process, &param[i], ocp)))
			check = 0;
		else if (ret[i] == 1 && i < 2)
			param[i] = cw_get_4(process->registries[param[i] - 1]);
		ocp = ocp << 2;
	}
	return (check);
}

int				cw_add(t_vm *vm, t_process *process)
{
	int				param[3];
	int				ret[3];

	process->pc = (process->pc + 1) % MEM_SIZE;
	if ((cw_add_param(vm, process, param, ret)))
	{
		cw_rev_get(process->registries[param[2] - 1], (unsigned int)
				(param[0] + param[1]));
		process->carry = !(param[0] + param[1]) ? 1 : 0;
		if (DEBUG)
			ft_printf("P    %d | add r%d r%d r%d\n",\
					process->id, param[0], param[1], param[2]);
	}
	process->pc = (process->pc + 1) % MEM_SIZE;
	return (1);
}
