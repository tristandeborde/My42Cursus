/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:59:21 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:49:10 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_count_digits(int n)
{
	int count;

	count = 0;
	if (n)
	{
		while (n)
		{
			n = (n - (n % 10)) / 10;
			count++;
		}
	}
	else
		count = 1;
	return (count);
}

char			*ft_itoa(int n)
{
	char			*result;
	int				count;
	int				sign;
	unsigned int	n_abs;

	sign = 1;
	n_abs = n;
	count = ft_count_digits(n);
	if (n < 0)
	{
		n_abs = -n;
		count++;
		sign = -1;
	}
	if (!(result = (char *)malloc(sizeof(char) * count + 1)))
		return (NULL);
	result[count] = '\0';
	while (count--)
	{
		result[count] = (n_abs % 10) + 48;
		n_abs = (n_abs - (n_abs % 10)) / 10;
	}
	if (sign < 0)
		result[0] = '-';
	return (result);
}
