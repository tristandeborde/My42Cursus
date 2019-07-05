/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:56:16 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 15:56:32 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*result;

	i = 0;
	if (!(ft_strlen(needle)))
		result = (char *)haystack;
	else
	{
		result = NULL;
		while (haystack[i] != '\0')
		{
			j = 0;
			while (haystack[i + j] == needle[j]
					&& needle[j] != '\0' && i + j < len)
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
