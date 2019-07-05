/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:35:41 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 17:04:55 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <string.h>

char	*ft_strtrim(char const *s)
{
	int	start;
	int	end;

	start = 0;
	if (s <= 0)
		return (ft_strnew(0));
	while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		start++;
	end = ft_strlen((char *)s) - 1;
	while (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')
		end--;
	if (start > end)
		return (ft_strnew(0));
	else
		return (ft_strsub(s, start, end + 1 - start));
}
