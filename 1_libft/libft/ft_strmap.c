/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:15:44 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:00:19 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <string.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*old_str;
	char	*new_str;

	i = 0;
	old_str = (char *)s;
	if (!s || !f ||
			!(new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		new_str[i] = (*f)(s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
