/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:02:11 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:08:54 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*dst_str;
	const char		*src_str;

	dst_str = dst;
	src_str = src;
	i = -1;
	while (++i < n)
		dst_str[i] = src_str[i];
	return (dst);
}
