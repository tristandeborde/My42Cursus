/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:24:35 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/30 13:06:49 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int			ft_apply_precision_int(char **ret, t_opt tab)
{
	char	*tmp;
	char	*tmp2;
	int		len;
	char	sign;

	len = ft_strlen(*ret);
	sign = (**ret == '+' || **ret == '-') ? **ret : 0;
	if (**ret == '+' || **ret == '-')
		len--;
	if (!(tab.is_true) || tab.is_true <= len)
		return (0);
	tmp = ft_strnew(tab.is_true + 1);
	tmp = ft_memset(tmp, '0', tab.is_true);
	if (sign)
	{
		*tmp = sign;
		**ret = '0';
	}
	tmp2 = tmp;
	tmp += tab.is_true - len;
	tmp = ft_strcpy(tmp, *ret);
	free(*ret);
	*ret = tmp2;
	return (1);
}

int			ft_apply_precision_char(char **ret, t_opt *tab, int error_code)
{
	char	*tmp;
	int		i;
	int		precision;

	i = ft_search_tab(tab, "precision");
	precision = i >= 0 ? tab[i].is_true : 0;
	if (error_code == -1 && precision > (int)ft_strlen(*ret))
		return (0);
	if (precision < (int)ft_strlen(*ret))
	{
		precision = precision ? precision : 1;
		tmp = ft_strnew(precision);
		tmp = ft_strncpy(tmp, *ret, precision);
		free(*ret);
		*ret = tmp;
		ft_unistr_trunc(ret, precision);
	}
	return (1);
}

int			ft_apply_precision_str(char **ret, t_opt *tab, int error_code)
{
	char	*tmp;
	int		i;
	int		precision;

	i = ft_search_tab(tab, "precision");
	precision = i >= 0 ? tab[i].is_true : 0;
	if (error_code == -1 && precision > (int)ft_strlen(*ret))
		return (0);
	if (precision < (int)ft_strlen(*ret))
	{
		tmp = ft_strnew(precision ? precision : 1);
		tmp = ft_strncpy(tmp, *ret, precision);
		free(*ret);
		*ret = tmp;
		ft_unistr_trunc(ret, precision);
	}
	return (1);
}
