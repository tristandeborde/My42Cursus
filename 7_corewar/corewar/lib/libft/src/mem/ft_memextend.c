/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memextend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:06:01 by cmaxime           #+#    #+#             */
/*   Updated: 2018/05/02 11:57:24 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memextend(char *dst, char *src, size_t sz_d, size_t sz_s)
{
	char	*tmp;

	dst = ft_memrealloc(dst, sz_d + sz_s, sz_d);
	tmp = dst + sz_d;
	tmp = ft_memcpy(tmp, src, sz_s);
	return (dst);
}
