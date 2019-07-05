/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_core_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 09:11:00 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/28 14:30:47 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_core_loop(t_vm vm)
{
	int	cycle;

	cycle = 0;
	while (1)
	{
		if (DEBUG)
			ft_printf("It is now cycle: %d\n", cycle);
		cw_process_process(&vm, cycle);
		if (cycle >= vm.loop.next_cycle_to_die)
		{
			cw_check_process(&vm, cycle >= vm.loop.next_max_check);
			vm.loop.next_cycle_to_die += vm.loop.cycle_to_die;
		}
		if (cycle == vm.setting.nbr_cycle)
			cw_dump_and_quit(&vm);
		cycle++;
		vm.cycle = cycle;
		if (BONUS)
			usleep(vm.setting.time);
	}
}
