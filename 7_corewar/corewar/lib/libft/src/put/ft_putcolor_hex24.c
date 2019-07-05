/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcolor_hex24.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:26:51 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/01 09:39:19 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_hexaconvertor_aux(char *tmp, int val)
{
	char	*rgb_val;

	if (!(rgb_val = ft_itoa((val))))
		return (0);
	tmp = ft_memcpy_x(tmp, ";", sizeof(char));
	tmp = ft_memcpy_x(tmp, rgb_val, sizeof(char) * ft_strlen(rgb_val));
	ft_strdel((char **)&rgb_val);
	return (tmp);
}

static char		*ft_hexaconvertor(long color)
{
	char	*color_code;
	char	*tmp;

	if (!(color_code = (char *)ft_memalloc(sizeof(char) * (19 + 1))))
		return (0);
	tmp = color_code;
	tmp = ft_memcpy_x(tmp, "\33[38;2", sizeof(char) * 6);
	if (!(tmp = ft_hexaconvertor_aux(tmp, ((color >> 16) & 0xFF))))
		return (0);
	if (!(tmp = ft_hexaconvertor_aux(tmp, ((color >> 8) & 0xFF))))
		return (0);
	if (!(tmp = ft_hexaconvertor_aux(tmp, (color & 0xFF))))
		return (0);
	tmp = ft_memcpy_x(tmp, "m", sizeof(char));
	*tmp = '\0';
	return (color_code);
}

extern void		ft_putcolor_hex24(long color, const char *str)
{
	char	*color_str;
	char	*tmp;
	char	*color_code;
	int		len;

	len = (str != 0) ? ft_strlen(str) : 0;
	if ((color_str = (char *)ft_memalloc(sizeof(char) * (22 + len + 1))))
	{
		tmp = color_str;
		if (!!(color_code = ft_hexaconvertor(color)))
		{
			tmp = ft_memcpy_x(tmp, color_code, sizeof(char) * \
				ft_strlen(color_code));
			ft_strdel((char **)&color_code);
		}
		if (len > 0)
			tmp = ft_memcpy_x(tmp, str, sizeof(char) * len);
		tmp = ft_memcpy_x(tmp, "\33[0m", sizeof(char) * 4);
		*tmp = '\0';
		ft_putstr(color_str);
		ft_strdel((char **)&color_str);
	}
}
