/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:32:50 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:18:24 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** retourne un pointeur sur la premiere occurence de la chaine to_find trouvé
** dans les n premier caractere de str, sinon retourne null (0). Les caractetes
** apres la fin de chaine str ne sont pas pris en compt,
*/

char		*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t i;
	size_t j;
	size_t len;

	len = ft_strlen(to_find);
	if (ft_strcmp(str, to_find) == 0 && n == ft_strlen(str))
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && (int)i <= (int)(n - len))
	{
		j = 0;
		while (to_find[j] == str[i + j] && to_find[j] != '\0' &&
				str[i + j] != '\0')
			j++;
		if (to_find[j] == '\0')
			return ((char *)(str + i));
		i++;
	}
	return (0);
}
