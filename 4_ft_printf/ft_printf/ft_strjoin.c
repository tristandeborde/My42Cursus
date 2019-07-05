/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:35:41 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/30 16:05:22 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;

	if (!s1 || !s2 ||
		!(new_str = (char *)malloc(sizeof(char) * ft_strlen((char *)s1) +
					ft_strlen((char *)s2) + 1)))
		return (NULL);
	new_str = ft_strcpy(new_str, (char *)s1);
	new_str = ft_strcat(new_str, (char *)s2);
	return (new_str);
}
