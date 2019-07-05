/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:54:04 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:09 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *ptrd, const void *ptrs, size_t n)
{
	unsigned char	*tmp_ptrd;
	unsigned char	*tmp_ptrs;
	int				ope;
	int				end;

	tmp_ptrd = (unsigned char *)ptrd;
	tmp_ptrs = (unsigned char *)ptrs;
	ope = 1;
	end = n + 1;
	if (tmp_ptrd > tmp_ptrs)
	{
		tmp_ptrd--;
		tmp_ptrs--;
		tmp_ptrd += n;
		tmp_ptrs += n;
		ope = -ope;
		end = 0;
	}
	while (tmp_ptrs != (ptrs + end - 1) && tmp_ptrd != tmp_ptrs)
	{
		*tmp_ptrd = *tmp_ptrs;
		tmp_ptrd += ope;
		tmp_ptrs += ope;
	}
	return (ptrd);
}
