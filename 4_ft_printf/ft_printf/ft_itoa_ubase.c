/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ubase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:59:21 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/12 14:52:59 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_count_digits(uintmax_t n, int base)
{
	int count;

	count = 0;
	while (n)
	{
		n = (n - (n % base)) / base;
		count++;
	}
	return (count);
}

char			*ft_itoa_ubase(uintmax_t n, int base)
{
	char			*result;
	int				count;
	char			*conversion;

	count = ft_count_digits(n, base);
	if (!count)
		count = 1;
	conversion = ft_strdup("0123456789abcdef");
	if (!(result = (char *)malloc(sizeof(char) * count + 1)))
		return (NULL);
	result[count] = '\0';
	while (count--)
	{
		result[count] = conversion[(n % base)];
		n = (n - (n % base)) / base;
	}
	free(conversion);
	return (result);
}
