/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 14:51:20 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/07 14:37:03 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_apply_options_int(char **ret, t_opt *tab, char conv, int error_code)
{
	t_padding	padding;
	char		*tmp;
	int			i;
	int			base;

	if ((i = ft_search_tab(tab, "width")) >= 0
			&& !(tmp = ft_strnew(tab[i].is_true + 1)))
		return (error_code == -42);
	tmp = i < 0 ? ft_strnew(2) : tmp;
	padding = ft_find_padding(tab, conv);
	base = tab[ft_search_tab(tab, "base")].is_true;
	if (!ft_atoi_base(*ret, base) && ft_search_tab(tab, ".") >= 0
				&& (i = ft_search_tab(tab, "precision")) == -1)
		ft_realloc(ret, 0, 1);
	if ((i = ft_search_tab(tab, "precision")) >= 0)
		ft_apply_precision_int(ret, tab[i]);
	if (ft_atoi_base(*ret, base) < 0 || ft_search_tab(tab, "+") >= 0)
		ft_place_sign(tab, padding, ret, &tmp);
	ft_write_padding(ret, tab, padding, &tmp);
	if (ft_search_tab(tab, " ") >= 0 && (!(**ret) || ft_atoi_base(*ret, base)
				>= 0) && ft_search_tab(tab, "+") < 0)
		ft_apply_space(ret, tab);
	free(padding.hashtag);
	return (1);
}

int	ft_apply_options_uint(char **ret, t_opt *tab, char conv, int error_code)
{
	t_padding	padding;
	char		*tmp;
	int			i;
	int			base;

	if ((i = ft_search_tab(tab, "width")) >= 0
			&& !(tmp = ft_strnew(tab[i].is_true + 3)))
		return (error_code == -42);
	tmp = i < 0 ? ft_strnew(2) : tmp;
	padding = ft_find_padding(tab, conv);
	base = tab[ft_search_tab(tab, "base")].is_true;
	if (!ft_atoi_base(*ret, base) && ft_search_tab(tab, ".") >= 0
				&& (i = ft_search_tab(tab, "precision")) == -1
				&& !(ft_strchr("oO", conv) && ft_search_tab(tab, "#") > 0))
		ft_realloc(ret, 0, 1);
	if ((i = ft_search_tab(tab, "precision")) >= 0)
		ft_apply_precision_int(ret, tab[i]);
	if ((ft_search_tab(tab, "#") > 0 && ft_atoi_ubase(*ret, base)
		&& !((conv == 'o' || conv == 'O') && **ret == '0')) || conv == 'p')
		ft_apply_hashtag(ret, padding, &tmp, tab);
	free(padding.hashtag);
	ft_write_padding(ret, tab, padding, &tmp);
	if ((i = ft_search_tab(tab, " ")) >= 0 && !ft_atoi_ubase(*ret, base))
		ft_apply_space(ret, tab);
	return (1);
}

int	ft_apply_options_char(char **ret, t_opt *tab, char conv, int error_code)
{
	t_padding	padding;
	char		*tmp;
	int			i;
	int			width_i;

	if ((width_i = ft_search_tab(tab, "width")) >= 0
			&& !(tmp = ft_strnew(tab[width_i].is_true)))
		return (0);
	tmp = width_i < 0 ? ft_strnew(2) : tmp;
	if ((i = ft_search_tab(tab, ".")) >= 0)
		ft_apply_precision_char(ret, tab, 1);
	if (conv)
		padding = ft_find_padding_char(tab);
	else
	{
		padding = ft_find_padding_percent(tab);
		padding.f = &ft_simple_return;
	}
	ft_write_padding_char(ret, tab, padding, &tmp);
	(void)error_code;
	return (1);
}

int	ft_apply_options_str(char **ret, t_opt *tab, char conv, int error_code)
{
	t_padding	padding;
	char		*tmp;
	int			i;
	int			width_i;

	i = 1;
	if ((width_i = ft_search_tab(tab, "width")) >= 0
			&& !(tmp = ft_strnew(tab[width_i].is_true + 1)))
		return (0);
	tmp = width_i < 0 ? ft_strnew(2) : tmp;
	if ((i = ft_search_tab(tab, ".")) >= 0 && conv != '%')
		i = ft_apply_precision_str(ret, tab, error_code);
	else if (error_code == -1)
	{
		free(tmp);
		ft_free_null(ret);
		return (0);
	}
	padding = ft_find_padding_char(tab);
	ft_write_padding_str(ret, tab, padding, &tmp);
	if (!i)
		ft_free_null(ret);
	return (i);
}

int	ft_apply_options_percent(char **ret, t_opt *tab, char conv, int error_code)
{
	t_padding	padding;
	char		*tmp;
	int			i;
	int			width_i;

	i = 1;
	if ((width_i = ft_search_tab(tab, "width")) >= 0
			&& !(tmp = ft_strnew(tab[width_i].is_true)))
		return (0);
	tmp = width_i < 0 ? ft_strnew(2) : tmp;
	if ((i = ft_search_tab(tab, ".")) >= 0 && conv != '%')
		i = ft_apply_precision_str(ret, tab, error_code);
	else if (error_code == -1)
	{
		free(tmp);
		ft_free_null(ret);
		return (0);
	}
	padding = ft_find_padding_percent(tab);
	ft_write_padding_str(ret, tab, padding, &tmp);
	if (!i)
		ft_free_null(ret);
	return (i);
}
