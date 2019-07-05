/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:57:13 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 15:54:43 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*save;

	i = -1;
	save = NULL;
	while (s[++i] != '\0')
	{
		if (s[i] == c)
			save = (char *)&s[i];
	}
	if (c == '\0')
		save = (char *)&s[i];
	return (save);
}
