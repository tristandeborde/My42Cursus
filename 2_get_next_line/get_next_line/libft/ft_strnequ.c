/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:31:48 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 17:16:40 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n)
		i++;
	if (s1[i] != s2[i] && i != n)
		return (0);
	else
		return (1);
}
