/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_sqrt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:15:14 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/29 13:28:30 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sqrt(int nb, int div)
{
	if (div == 1)
		return (0);
	else if (div * div == nb)
		return (div);
	else
		return (ft_sqrt(nb, div - 1));
}

int			ft_next_sqrt(int nb)
{
	int div;

	div = ft_sqrt(nb, nb / 2);
	if (div)
		return (div);
	else
		return (ft_next_sqrt(nb + 1));
}
