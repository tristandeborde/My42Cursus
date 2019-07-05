/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:47:40 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:18:32 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** Creer un copie de la sous chaine s passé en paramettre, cette sous chaine
** commence à l'index start et est de longueur len.
*/

char		*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char			*cpy;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if ((cpy = (char *)(malloc(sizeof(char) * (len + 1)))) == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = s[start + i];
		i++;
	}
	cpy[len] = '\0';
	return (cpy);
}
