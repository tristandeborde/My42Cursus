/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:32:26 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:26:41 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int					i;
	int					result;
	int					sign;
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
