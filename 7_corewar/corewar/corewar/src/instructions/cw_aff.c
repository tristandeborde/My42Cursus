/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:41:19 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/28 15:42:48 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	cw_ocp(int ocp, t_process *process)
{
	if ((ocp & 0xc0) != 0x40)
	{
		if (DEBUG)
			ft_printf("P    %d | aff: bad ocp %02x %d\n", \
				process->id, ocp, cw_ocp_offset(ocp, 0, 1));
		process->pc = (process->pc + cw_ocp_offset(ocp, 0, 1)) % MEM_SIZE;
		return (0);
	}
	return (ocp);
}

int			cw_aff(t_vm *vm, t_process *process)
{
	int				param;
	unsigned char	aff;

	process->pc = (process->pc + 1) % MEM_SIZE;
	if (cw_ocp(vm->vm[(process->pc + process->entrypoint) % MEM_SIZE], \
		process))
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		param = cw_get_1(&(vm->vm[(process->pc + process->entrypoint + 2)
					% MEM_SIZE]));
		if (cw_check_reg(param))
		{
			aff = cw_get_4(process->registries[param - 1]) % 256;
			ft_printf("%C\n", aff);
			if (DEBUG)
				ft_printf("P    %d | aff r%d\n", process->id, param);
		}
		process->pc = (process->pc + 1) % MEM_SIZE;
	}
	else
		process->pc = (process->pc + 1) % MEM_SIZE;
	return (1);
}
