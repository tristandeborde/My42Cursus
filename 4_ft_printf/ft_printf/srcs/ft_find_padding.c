/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_padding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:37:41 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/26 11:40:51 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char		*ft_simple_return(char *str1, const char *str2, size_t len)
{
	(void)str2;
	(void)len;
	return (str1);
}

t_padding	ft_find_padding(t_opt *tab, char conv)
{
	t_padding padding;

	padding.padding = 0;
	padding.f = &ft_strncat;
	if (ft_search_tab(tab, "-") > 0)
	{
		padding.padding = ' ';
		padding.f = &ft_strncpy;
	}
	else if (ft_search_tab(tab, ".") > 0)
		padding.padding = ' ';
	else if (ft_search_tab(tab, "0") > 0)
		padding.padding = '0';
	else if (padding.padding == 0)
		padding.padding = ' ';
	padding.hashtag = ft_strchr("xXp", conv) ? ft_strdup("0x") : ft_strdup("0");
	return (padding);
}

t_padding	ft_find_padding_char(t_opt *tab)
{
	t_padding padding;

	padding.padding = 0;
	padding.f = &ft_strncat;
	if (ft_search_tab(tab, "-") > 0)
	{
		padding.padding = ' ';
		padding.f = &ft_strncpy;
	}
	else if (ft_search_tab(tab, "0") > 0)
		padding.padding = '0';
	else if (padding.padding == 0)
		padding.padding = ' ';
	return (padding);
}

t_padding	ft_find_padding_percent(t_opt *tab)
{
	t_padding padding;

	padding.padding = 0;
	padding.f = &ft_strncat;
	if (ft_search_tab(tab, "-") > 0)
	{
		padding.padding = ' ';
		padding.f = &ft_strncpy;
	}
	else if (ft_search_tab(tab, ".") > 0)
		padding.padding = ' ';
	if (ft_search_tab(tab, "0") > 0)
		padding.padding = '0';
	else if (padding.padding == 0)
		padding.padding = ' ';
	return (padding);
}
