/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:12:54 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:05 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Vérifie si l'intervalle mememoir encadré par [ptr1 ; ptr1 + n] comporte des
** adresse identiques à l'intervalle encadré par [ptr2 ; ptr2 + n]
*/

int		ft_memjunc(void *ptr1, void *ptr2, size_t n)
{
	unsigned char *lower_addr;
	unsigned char *highest_addr;

	if (ptr1 != ptr2)
	{
		lower_addr = ptr1;
		highest_addr = ptr2;
		if (ptr2 > ptr1)
		{
			lower_addr = ptr2;
			highest_addr = ptr1;
		}
		return ((lower_addr + n >= highest_addr) ? -1 : 1);
	}
	return (0);
}
