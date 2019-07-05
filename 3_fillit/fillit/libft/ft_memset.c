/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:16:51 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:11 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Remplie les n premiere adresse pointé par ptr de la valeur indiqué par c.
*/

void		*ft_memset(void *ptr, int c, size_t n)
{
	unsigned char	*tmp_ptr;

	if (n)
		tmp_ptr = ptr;
	while (n--)
		*(tmp_ptr++) = c;
	return (ptr);
}
