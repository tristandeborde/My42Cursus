/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:50:39 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:15:17 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Verifie si la valeur int passé en parametre correspond à un caractere
** alphabetique.
*/

int		ft_isalpha(int c)
{
	return ((ft_isupper(c) || ft_islower(c)) ? 1 : 0);
}
