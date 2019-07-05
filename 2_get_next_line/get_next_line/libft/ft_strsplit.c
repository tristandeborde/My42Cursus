/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:39:48 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 17:43:45 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count(char const *s, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0' && !count)
			return (0);
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
		count++;
	}
	return (count);
}

static char	**ft_gen_tab(char **tab, char const *s, char c)
{
	int start;
	int end;
	int i;

	i = 0;
	start = 0;
	end = 0;
	while (s[end] != '\0')
	{
		start = end;
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end] != '\0')
			end++;
		tab[i] = ft_strsub(s, start, end - start);
		while (s[end] == c && s[end] != '\0')
			end++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		count;

	if (!s)
		return (NULL);
	count = ft_count(s, c);
	if (!(tab = (char**)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	tab[0] = 0;
	if (count)
		tab = ft_gen_tab(tab, s, c);
	return (tab);
}
