/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:48:45 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:16:52 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** La fonction ft_memchr, cherche l'occurence c, dans l'élément pointé par  s.
*/

void		*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*tmp_s;
	unsigned char		to_find;

	if (n != 0)
	{
		tmp_s = s;
		to_find = (unsigned char)c;
		while (n != 0)
		{
			if (*tmp_s++ == to_find)
				return ((void *)(tmp_s - 1));
			n--;
		}
	}
	return (0);
}
