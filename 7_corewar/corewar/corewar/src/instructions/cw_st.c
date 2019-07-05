/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:44:33 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/27 18:13:29 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_ocp(int ocp, t_process *process)
{
	if ((ocp & 0xf0) != 0x50 && (ocp & 0xf0) != 0x70)
	{
		if (DEBUG)
			ft_printf("st: bad ocp %02x %d\n", ocp, cw_ocp_offset(ocp, 0, 2));
		process->pc = (process->pc + cw_ocp_offset(ocp, 0, 2)) % MEM_SIZE;
		return (0);
	}
	return (ocp);
}

int				cw_st_param(t_vm *vm, t_process *process, int param[2],
		int ret[2])
{
	int				i;
	int				check;
	unsigned char	ocp;

	i = -1;
	check = 1;
	if (!(ocp = cw_ocp(vm->vm[(process->pc + process->entrypoint) % MEM_SIZE],
		process)))
		return (0);
	while (++i < 2)
	{
		if (!(ret[i] = cw_read_ocp(vm, process, &param[i], ocp)))
			check = 0;
		ocp = ocp << 2;
	}
	return (check);
}

int				cw_st(t_vm *vm, t_process *process)
{
	int				param[2];
	int				ret[2];

	process->pc = (process->pc + 1) % MEM_SIZE;
	if ((cw_st_param(vm, process, param, ret)))
	{
		if (ret[1] == 1)
			ft_memcpy(process->registries[param[1] - 1],
					process->registries[param[0] - 1], REG_SIZE);
		else
			cw_memcpy_to_circle(vm->vm, process->registries[param[0] - 1],
			(unsigned int)(process->pc + process->entrypoint +
			((short)param[1] % IDX_MOD) - ret[1] - 2) % MEM_SIZE, REG_SIZE);
		if (DEBUG)
		{
			ft_printf("P    %d | st: r%d (%d) -> %.1s%d\n", \
				process->id, param[0], cw_get_4(process->registries[\
					param[0] - 1]), ret[1] == 1 ? "r" : "", param[1]);
		}
	}
	process->pc = (process->pc + 1) % MEM_SIZE;
	return (1);
}
