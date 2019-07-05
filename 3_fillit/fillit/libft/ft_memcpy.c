/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:49:56 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:16:59 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *ptrd, const void *ptrs, size_t n)
{
	unsigned char	*tmp_ptrd;
	unsigned char	*tmp_ptrs;

	if (n != 0)
	{
		tmp_ptrd = (unsigned char *)ptrd;
		tmp_ptrs = (unsigned char *)ptrs;
		while (n--)
			*tmp_ptrd++ = *tmp_ptrs++;
	}
	return (ptrd);
}
