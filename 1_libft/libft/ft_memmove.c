/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:20:25 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:48:47 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static int		ft_ptrcmp(const unsigned char *src, unsigned char *dst)
{
	if (src == dst)
		return (0);
	if (src < dst)
		return (1);
	else
		return (-1);
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char *src_str;
	unsigned char		*dst_str;
	unsigned int		i;

	src_str = src;
	dst_str = dst;
	if (!(ft_ptrcmp(src_str, dst_str)))
		return (NULL);
	else if (ft_ptrcmp(src_str, dst_str) > 0)
	{
		i = len;
		while (i--)
			dst_str[i] = src_str[i];
	}
	else
	{
		i = -1;
		while (++i < len)
			dst_str[i] = src_str[i];
	}
	return (dst);
}
