/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:26:34 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/01 09:40:02 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

static int		ft_checkcolor_code(const char *color)
{
	int			val;

	if (color == 0)
		return (0);
	if (!ft_strisdigit(color))
		return (0);
	val = ft_atoi(color);
	if (val < 0 || 255 < val)
		return (0);
	return (1);
}

extern void		ft_putcolor_8(const char *color, const char *str)
{
	char		*color_str;
	char		*tmp;
	int			len;

	if (ft_checkcolor_code(color) == 1)
	{
		len = (str != 0) ? ft_strlen(str) : 0;
		if ((color_str = (char *)ft_memalloc(sizeof(char) * (10 + len + 1))))
		{
			tmp = color_str;
			tmp = ft_memcpy_x(tmp, "\33[", sizeof(char) * 2);
			tmp = ft_memcpy_x(tmp, color, sizeof(char) * ft_strlen(color));
			tmp = ft_memcpy_x(tmp, "m", sizeof(char) * 1);
			tmp = ft_memcpy_x(tmp, str, sizeof(char) * len);
			tmp = ft_memcpy_x(tmp, "\33[0m", sizeof(char) * 4);
			*tmp = '\0';
			ft_putstr(color_str);
			ft_strdel((char **)&color_str);
		}
	}
}
