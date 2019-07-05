/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 16:24:06 by pprikazs          #+#    #+#             */
/*   Updated: 2018/04/25 16:41:01 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** Return a bit to bit cpy of the two pointer but with head adress fix to
** the end au the cpy. Usefull for pre-allocation then kind of concatenation.
*/

void		*ft_memcpy_x(void *ptrd, const void *ptrs, size_t n)
{
	unsigned char	*tmp_ptrd;
	unsigned char	*tmp_ptrs;

	if (n != 0)
	{
		tmp_ptrd = (unsigned char *)ptrd;
		tmp_ptrs = (unsigned char *)ptrs;
		while (n--)
			*tmp_ptrd++ = *tmp_ptrs++;
		return ((void *)tmp_ptrd);
	}
	return (ptrd);
}
