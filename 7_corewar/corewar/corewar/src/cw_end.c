/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:11:23 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/05/02 11:34:08 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_dump_processes2(t_vm *vm, int i)
{
	t_list		*lst;
	t_process	*process;

	lst = vm->process;
	while (lst)
	{
		ft_putendl("");
		process = lst->content;
		ft_printf("P %d\n", process->id);
		i = 0;
		while (i < REG_NUMBER - 1)
		{
			ft_printf("%d|", cw_get_4(process->registries[i]));
			i++;
		}
		ft_printf("%d(registres)\n%-d\t(entrypoint)\n%-d\t(pc)\n%-d\t(carry)\n",
			cw_get_4(process->registries[i]), process->entrypoint, process->pc,
				process->carry);
		ft_printf("%-d\t(next_cycle)\n%-d\t(live)\n", process->next_cycle,
				process->live);
		lst = lst->next;
	}
}

void	cw_dump_all(t_vm *vm)
{
	int i;

	i = 0;
	while (i < vm->setting.nbr_champion)
	{
		ft_printf("Player %d: %s\n", vm->setting.champion_tab[i].id,
				vm->setting.champion_tab[i].name);
		i++;
	}
	cw_dump_processes2(vm, i);
}

void	cw_dump_and_quit(t_vm *vm)
{
	int		i;
	char	*res;

	res = 0;
	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		ft_printf("%02x", vm->vm[i]);
		if ((i + 1) % 32 != 0)
			ft_putchar(' ');
		else
		{
			ft_putstr(" \n");
			if (i != MEM_SIZE - 1)
				ft_printf("%#06x : ", i + 1);
		}
		i++;
	}
	if (BONUS)
		system("kill $(ps | grep afplay | cut -d ' ' -f 1)");
	if (DEBUG)
		cw_dump_all(vm);
	exit(0);
}

void	cw_game_over(t_vm *vm)
{
	t_champion	*champ;
	int			index;

	index = vm->loop.last_live.index;
	champ = cw_find_player(&(vm->setting), index);
	if (BONUS)
	{
		system("kill $(ps | grep afplay | cut -d ' ' -f 1)");
		system("afplay ../.media/victory.wav &");
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", index, champ->name);
	exit(0);
}
