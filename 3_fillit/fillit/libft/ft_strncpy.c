/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:08:17 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:18:19 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Copie les n premier caractere de la chaine src passé en parametre.
*/

char		*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	ft_memset(dest, '\0', n);
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
