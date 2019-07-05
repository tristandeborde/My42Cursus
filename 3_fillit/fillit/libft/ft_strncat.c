/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:07:42 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:18:15 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Concaten les n premier caractere de la chaine source et l'ajoute à la suite
** de dest puis la retourn.
*/

char		*ft_strncat(char *dest, const char *src, int nbr)
{
	int i;
	int dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	while (src[i] && i < nbr)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
