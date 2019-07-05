/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:17:49 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:30 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Imprime la chaine de caractere passé en parametre sur la sortie standard.
*/

void		ft_putstr(const char *str)
{
	if (str)
	{
		while (*str)
			ft_putchar(*str++);
	}
}
