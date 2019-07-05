/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcolor_24.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:40:05 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/01 09:39:38 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_checkcolor_code(const char *color)
{
	int			i;

	i = 1;
	if (color == 0 || ft_strlen(color) < 11)
		return (0);
	while (i < 12)
	{
		if (i % 4 == 0 && color[i - 1] != ';')
			return (0);
		else if (i % 4 != 0 && !(ft_isdigit(color[i - 1])))
			return (0);
		i++;
	}
	return (1);
}

extern void		ft_putcolor_24(const char *color, const char *str)
{
	char		*color_str;
	char		*tmp;
	int			len;

	if (ft_checkcolor_code(color) == 1)
	{
		len = (str != 0) ? ft_strlen(str) : 0;
		if ((color_str = (char *)ft_memalloc(sizeof(char) * (22 + len + 1))))
		{
			tmp = color_str;
			tmp = ft_memcpy_x(tmp, "\33[38;2;", sizeof(char) * 7);
			tmp = ft_memcpy_x(tmp, color, sizeof(char) * ft_strlen(color));
			tmp = ft_memcpy_x(tmp, "m", sizeof(char));
			tmp = ft_memcpy_x(tmp, str, sizeof(char) * len);
			tmp = ft_memcpy_x(tmp, "\33[0m", sizeof(char) * 4);
			*tmp = '\0';
			ft_putstr(color_str);
			ft_strdel((char **)&color_str);
		}
	}
}
