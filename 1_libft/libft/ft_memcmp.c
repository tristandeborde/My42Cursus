/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 11:50:29 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:22:40 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int		i;
	const unsigned char	*s1_cpy;
	const unsigned char	*s2_cpy;

	s1_cpy = s1;
	s2_cpy = s2;
	i = 0;
	if (!n)
		return (0);
	else
	{
		while (i < n && s1_cpy[i] == s2_cpy[i])
			i++;
		if (i == n)
			return (0);
		else
			return (s1_cpy[i] - s2_cpy[i]);
	}
}
