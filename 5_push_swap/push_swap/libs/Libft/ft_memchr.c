/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:59:26 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:31 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*tmp;

	i = -1;
	while (++i < n)
	{
		tmp = ((unsigned char *)&s[i]);
		if ((unsigned char)*tmp == (unsigned char)c)
			return ((void *)tmp);
	}
	return (NULL);
}
