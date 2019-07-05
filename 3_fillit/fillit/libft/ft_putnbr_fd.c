/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:06:44 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:27 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int nbr, int fd)
{
	int size;
	int tmp;

	if (nbr == -2147483648)
	{
		ft_putstr_fd("-2", fd);
		nbr = nbr % 2000000000;
		nbr = -nbr;
	}
	else if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	size = 1;
	tmp = nbr;
	while ((tmp = tmp / 10) != 0)
		size = size * 10;
	while (size)
	{
		ft_putchar_fd((char)((nbr / size) + 48), fd);
		nbr %= size;
		size /= 10;
	}
}
