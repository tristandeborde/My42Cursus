/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:45:54 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:16:49 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *ptrd, const void *ptrs, int c, size_t n)
{
	unsigned char	*tmp_ptrd;
	unsigned char	*tmp_ptrs;
	size_t			i;

	tmp_ptrd = (unsigned char *)ptrd;
	tmp_ptrs = (unsigned char *)ptrs;
	c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		*tmp_ptrd++ = *tmp_ptrs++;
		if (*(tmp_ptrd - 1) == c)
			return (tmp_ptrd);
		i++;
	}
	return (0);
}
