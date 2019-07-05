/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_unicode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:37:25 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/26 18:49:31 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <unistd.h>

void		ft_unistr_trunc(char **str, int precision)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = precision - 1;
	while (i < 4 && ((*str)[j] & 128) && !((*str)[j] & 64))
	{
		i++;
		j -= 1;
	}
	i++;
	tmp = (*str)[j];
	while (tmp & 128 && i > -2)
	{
		tmp = tmp << 1;
		i--;
	}
	if (i && ((*str)[j] & 128) && (*str)[j] & 64 && MB_CUR_MAX > 1)
		(*str)[j] = '\0';
}

int			ft_handle_unistr(wchar_t *uni_str, char **ret)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (!(*ret))
		*ret = ft_strnew(2);
	while (uni_str[i])
	{
		if (!(tmp = ft_handle_unicode(uni_str[i])))
		{
			free(tmp);
			return (-1);
		}
		tmp2 = *ret;
		*ret = ft_strjoin(tmp2, tmp);
		free(tmp2);
		free(tmp);
		i++;
	}
	return (1);
}

static int	ft_count_bytes(wchar_t uni_char)
{
	wchar_t	mask;
	int		i;
	int		byte_nb;

	i = 0;
	mask = 1;
	byte_nb = 0;
	while (mask < 2097152)
	{
		if (mask & uni_char)
			byte_nb = i;
		mask = mask << 1;
		i++;
	}
	return (byte_nb);
}

char		*ft_handle_unicode(wchar_t uni_char)
{
	int				byte_nb;
	char			*ret;

	if (!(ret = ft_strnew(5)))
		return (NULL);
	byte_nb = ft_count_bytes(uni_char);
	if (byte_nb == 7 && MB_CUR_MAX == 1)
		*ret = (char)uni_char;
	else
	{
		byte_nb = byte_nb < 7 ? 0 : (byte_nb - 1) / 5;
		if (byte_nb >= MB_CUR_MAX || uni_char > 1114111 || uni_char < 0 ||
				(uni_char >= 55296 && uni_char <= 57343))
		{
			free(ret);
			return (NULL);
		}
		else
			ft_n_bytes(uni_char, byte_nb, &ret);
	}
	return (ret);
}

void		ft_n_bytes(wchar_t uni_char, int byte_nb, char **ret)
{
	unsigned char	mask;
	int				i;

	i = 0;
	if (byte_nb > 0)
	{
		mask = 128;
		while (i < byte_nb + 1)
		{
			(*ret)[0] |= mask;
			mask = mask >> 1;
			i++;
		}
	}
	i = byte_nb;
	while (byte_nb > 0)
	{
		(*ret)[byte_nb] = 0;
		(*ret)[byte_nb] |= (uni_char & 63);
		(*ret)[byte_nb] |= 128;
		uni_char >>= 6;
		byte_nb--;
	}
	(*ret)[byte_nb] += uni_char;
}
