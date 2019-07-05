/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:02:11 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:09:24 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int		i;
	unsigned char		*dst_str;
	const unsigned char	*src_str;

	dst_str = dst;
	src_str = src;
	i = 0;
	while (i < n)
	{
		dst_str[i] = src_str[i];
		if (dst_str[i] == (unsigned char)c)
			return (&dst_str[i + 1]);
		i++;
	}
	return (NULL);
}
