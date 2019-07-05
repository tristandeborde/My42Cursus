/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:57:13 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:06:25 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = ft_strlen((char *)s);
	while (++i < len + 1)
	{
		tmp = ((char *)&s[i]);
		if (*tmp == c)
			return (tmp);
	}
	return (NULL);
}
