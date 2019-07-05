/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:04:15 by cmaxime           #+#    #+#             */
/*   Updated: 2018/05/02 12:01:32 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_strishexa(char *str)
{
	int		i;

	i = 1;
	if (str[0] != '0' && str[1] != 'x')
		return (0);
	while (str[++i] != '\0')
	{
		if (!(str[i] <= '9' && str[i] >= '0') && !(str[i] >= 'a'
					&& str[i] <= 'f') && !(str[i] >= 'A' && str[i] <= 'F'))
			return (0);
	}
	return (1);
}

char	*cw_strtolower(char *str)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] <= 'Z' && str[i] >= 'A')
			str[i] += 'A' - 'a';
	}
	return (str);
}

char	cw_get_op(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	while (str[++i] != '\0')
	{
		if (str[i] == '-' || str[i] == '+')
		{
			c = str[i];
			break ;
		}
	}
	if (str[i] == '\0' || str[i + 1] == '\0')
		return ('\0');
	while (str[++i] != '\0')
	{
		if (str[i] == '-' || str[i] == '+')
			c = '\0';
	}
	return (c);
}

int		ft_strisoperation(char *str, int *val)
{
	char	c;
	char	**tab;
	int		buff;
	int		ret;

	buff = 0;
	if ((c = cw_get_op(str)) == '\0')
		return (0);
	tab = ft_strsplit(str, c);
	ret = 1;
	ft_strsanitalize(tab[0], "\t ");
	ft_strsanitalize(tab[1], "\t ");
	if (!cw_parse_value(tab[0], val))
		ret = 0;
	if (!cw_parse_value(tab[1], &buff))
		ret = 0;
	ft_strdel_tab(tab);
	*val = (c == '-') ? *val - buff : *val + buff;
	return (ret);
}

int		cw_parse_value(char *str, int *val)
{
	if (ft_strisdigit(str))
	{
		*val = ft_atoi(str);
		return (1);
	}
	else if (ft_strishexa(str))
	{
		*val = ft_atoi_base(str + 2, "0123456789abcdef");
		return (1);
	}
	else if (ft_strisoperation(str, val))
		return (1);
	return (0);
}
