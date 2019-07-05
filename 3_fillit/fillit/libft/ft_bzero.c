/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:42:30 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:15:12 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Remplie les n premiere pointé par ptr de la valeur nul (0).
*/

void		*ft_bzero(void *ptr, size_t n)
{
	unsigned char	*tmp_ptr;

	if (n)
		tmp_ptr = ptr;
	while (n--)
		*tmp_ptr++ = 0;
	return (ptr);
}
