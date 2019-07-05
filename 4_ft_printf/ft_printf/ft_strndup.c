/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:41:19 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/25 10:57:33 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include <unistd.h>

char	*ft_strndup(const char *s1, int len)
{
	char	*s2;
	int		i;

	i = -1;
	if (!(s2 = (char *)malloc(sizeof(char) * len + 2)))
		return (NULL);
	while (++i < len)
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}
