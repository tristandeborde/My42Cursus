/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:56:40 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 15:54:17 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	if (!(ft_strlen(needle)))
		result = (char *)haystack;
	else
	{
		result = NULL;
		while (haystack[i] != '\0')
		{
			j = 0;
			while (haystack[i + j] == needle[j] && needle[j] != '\0')
				j++;
			if (needle[j] == '\0')
			{
				result = (char *)&haystack[i];
				return (result);
			}
			i++;
		}
	}
	return (result);
}
