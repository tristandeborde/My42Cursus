/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:32:26 by tdeborde          #+#    #+#             */
/*   Updated: 2017/12/21 12:58:17 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t		ft_atoi(const char *str)
{
	int					i;
	intmax_t			result;
	intmax_t			sign;
	const unsigned char	*s;

	i = 0;
	sign = 1;
	result = 0;
	s = (unsigned char *)str;
	while (s[i] == '\t' || s[i] == ' ' || s[i] == '\n' || s[i] == '\v'
			|| s[i] == '\f' || s[i] == '\r')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		result = (s[i] - 48) + (result * 10);
		i++;
	}
	return (result * sign);
}
