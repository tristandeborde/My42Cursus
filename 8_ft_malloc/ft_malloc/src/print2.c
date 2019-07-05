/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 14:05:22 by tdeborde          #+#    #+#             */
/*   Updated: 2019/06/05 11:38:23 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		ft_putunbr(size_t nb)
{
	char	c;

	c = 0;
	if (nb >= 10)
	{
		ft_putunbr(nb / 10);
		ft_putunbr(nb % 10);
	}
	else
	{
		c = nb + 48;
		write(1, &c, 1);
	}
}

void		ft_puthex(uintptr_t nb)
{
	int			i;
	char		buf[25];
	static char	repr[17] = "0123456789ABCDEF";

	nb &= 0xffffffff;
	i = 0;
	while (nb > 0)
	{
		buf[i++] = repr[nb % 16];
		nb /= 16;
	}
	while (i < 8)
		buf[i++] = '0';
	write(1, "0x", 2);
	while (i >= 0)
		write(1, &buf[--i], 1);
}
