/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 09:21:32 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/26 13:03:07 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cw_check_live(t_process *process, void *none)
{
	none = 0;
	if (process->live > 0)
		return (1);
	return (0);
}

void	cw_check_process(t_vm *vm, int max)
{
	t_list		*curr;
	int			live;

	ft_lstdelif(&(vm->process), 0, &cw_check_live);
	curr = vm->process;
	while (curr)
	{
		((t_process*)curr->content)->live = 0;
		curr = curr->next;
	}
	live = vm->loop.nb_live;
	if (live == 0)
		cw_game_over(vm);
	if (live >= NBR_LIVE || max)
	{
		vm->loop.cycle_to_die -= CYCLE_DELTA;
		vm->loop.next_max_check = vm->cycle + vm->loop.cycle_to_die
			* MAX_CHECKS;
	}
	vm->loop.nb_live = 0;
	ft_printf("Cycle to die is now %d, %d live\n", vm->loop.cycle_to_die,
			live);
}
