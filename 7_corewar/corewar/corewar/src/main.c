/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:56:30 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/05/01 17:46:08 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_champions_data(t_setting *setting)
{
	int			i;
	t_champion	*c;
	int			j;

	c = setting->champion_tab;
	ft_putendl("Champion data");
	i = -1;
	while (++i < setting->nbr_champion)
	{
		ft_putendl(c[i].name);
		ft_printf("%d\n", c[i].id);
		ft_printf("%d\n", c[i].size_prog);
		j = -1;
		while (++j < c[i].size_prog)
			ft_printf("%02hhx ", c[i].bin[j]);
		ft_putchar('\n');
	}
}

int		main(int ac, char **av)
{
	t_vm		vm;

	cw_vm_init(&vm, ac, av);
	if (DEBUG)
		print_champions_data(&(vm.setting));
	if (BONUS)
	{
		system("afplay ../.media/battle.mp3 &");
		system("afplay ../.media/music.mp3 &");
		system("afplay ../.media/sword.mp3 &");
	}
	cw_core_loop(vm);
	return (0);
}
