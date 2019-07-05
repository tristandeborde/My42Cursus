/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:49:17 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:16:55 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** La fonction ft_memcmp compare le n premier byte des valeurs pointés par
** s1 et s2.
*/

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*tmp_s1;
	const unsigned char	*tmp_s2;

	tmp_s1 = s1;
	tmp_s2 = s2;
	while (n != 0)
	{
		if (*tmp_s1++ != *tmp_s2++)
			return ((int)(*(tmp_s1 - 1) - *(tmp_s2 - 1)));
		n--;
	}
	return (0);
}
