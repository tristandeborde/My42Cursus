/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:35:41 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/26 17:54:54 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnjoin(char const *s1, char *s2, unsigned int len1,
		unsigned int len2)
{
	char			*new_str;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2 ||
		!(new_str = (char *)malloc(sizeof(char) * \
				(len1 + len2 + 1))))
		return (NULL);
	i = -1;
	while (++i < len1)
		new_str[i] = s1[i];
	j = -1;
	while (++j < len2)
		new_str[i + j] = s2[j];
	new_str[i + j] = '\0';
	return (new_str);
}
