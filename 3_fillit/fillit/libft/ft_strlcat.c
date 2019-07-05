/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:59:05 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:18:07 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	d_end;

	i = 0;
	while (dest[i] && i < size)
		i++;
	d_end = i;
	while (src[i - d_end] && (int)i < (int)size - 1)
	{
		dest[i] = src[i - d_end];
		i++;
	}
	if (d_end < size)
		dest[i] = '\0';
	return (d_end + ft_strlen(src));
}
