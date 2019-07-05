/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_op_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 20:20:14 by tdeborde          #+#    #+#             */
/*   Updated: 2018/04/27 16:27:37 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_champion	*cw_find_player(t_setting *setting, int index)
{
	int	i;

	i = setting->nbr_champion;
	while (--i >= 0)
	{
		if (setting->champion_tab[i].id == index)
			return (&(setting->champion_tab[i]));
	}
	return (0);
}

int			cw_get_1(unsigned char *vm)
{
	return (vm[0]);
}

int			cw_get_2(unsigned char *vm)
{
	return (vm[0] << 8 | vm[1]);
}

int			cw_get_4(unsigned char *vm)
{
	return (vm[0] << 24 | vm[1] << 16 | vm[2] << 8 | vm[3]);
}

int			cw_check_reg(int param)
{
	if (param < 1 || param > REG_NUMBER)
	{
		ft_printf("Op failed : no registries found for reg_index %d\n", param);
		return (0);
	}
	return (1);
}
