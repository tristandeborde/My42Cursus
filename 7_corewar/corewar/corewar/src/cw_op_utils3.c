/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_op_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 20:20:14 by tdeborde          #+#    #+#             */
/*   Updated: 2018/04/25 16:27:12 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		*cw_memcpy_to_circle(void *dst, void *src, int off, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		*((unsigned char*)dst + (i + off) % MEM_SIZE) = *((unsigned char*)src
				+ (i));
		i++;
	}
	return (dst);
}

void		*cw_memcpy_from_circle(void *dst, void *src, int off, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		*((unsigned char*)dst + i) = *((unsigned char*)src + (i + off)
				% MEM_SIZE);
		i++;
	}
	return (dst);
}

int			cw_get_int(unsigned char *vm, int off, int len)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (i < len)
	{
		res = res << 8;
		res = res | *((unsigned char*)vm + (i + off) % MEM_SIZE);
		i++;
	}
	return (res);
}
