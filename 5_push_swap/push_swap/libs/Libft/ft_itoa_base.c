/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:59:21 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/12 14:52:54 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_count_digits(uintmax_t n_abs, int base)
{
	int count;

	count = 0;
	while (n_abs)
	{
		n_abs = (n_abs - (n_abs % base)) / base;
		count++;
	}
	return (count);
}

char			*ft_itoa_base(intmax_t n, int base)
{
	char			*result;
	int				count;
	int				sign;
	uintmax_t		n_abs;
	char			*conversion;

	sign = n >= 0 ? 1 : -1;
	n_abs = n > 0 ? n : -n;
	count = ft_count_digits(n_abs, base);
	if (n <= 0)
		count++;
	conversion = ft_strdup("0123456789abcdef");
	if (!(result = (char *)malloc(sizeof(char) * count + 1)))
		return (NULL);
	result[count] = '\0';
	while (count--)
	{
		result[count] = conversion[(n_abs % base)];
		n_abs = (n_abs - (n_abs % base)) / base;
	}
	if (sign < 0)
		result[0] = '-';
	free(conversion);
	return (result);
}
