/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:00:40 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:18:41 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Verifie si la valeur int passé en paramettre correspond à une minuscule et
** la transforme en majuscule.
*/

int		ft_toupper(int c)
{
	return ((ft_islower(c)) ? c - 32 : c);
}
