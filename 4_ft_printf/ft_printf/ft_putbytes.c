/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:41:59 by tdeborde          #+#    #+#             */
/*   Updated: 2017/12/27 16:08:00 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_putbytes(char const *s, int len)
{
	int i;

	i = 0;
	if (s != NULL)
	{
		while (i < len)
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}
