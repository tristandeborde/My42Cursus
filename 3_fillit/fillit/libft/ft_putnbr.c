/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:26:09 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:25 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Imprime en code ascii sur la sortie standard la valeur int passé en
** parametre.
*/

void		ft_putnbr(int nbr)
{
	int size;
	int tmp;

	if (nbr == -2147483648)
	{
		ft_putstr("-2");
		nbr = nbr % 2000000000;
		nbr = -nbr;
	}
	else if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	size = 1;
	tmp = nbr;
	while ((tmp = tmp / 10) != 0)
		size = size * 10;
	while (size)
	{
		ft_putchar((char)((nbr / size) + 48));
		nbr %= size;
		size /= 10;
	}
}
