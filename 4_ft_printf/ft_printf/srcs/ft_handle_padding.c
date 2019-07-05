/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:25:20 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/30 13:07:07 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void		ft_write_padding(char **ret, t_opt *tab, t_padding padding,
		char **tmp)
{
	int		i;
	int		width_i;

	if ((i = ft_search_tab(tab, "width") >= 0)
			&& (width_i = tab[i].is_true) > (int)ft_strlen(*ret))
	{
		ft_realloc(tmp, **tmp != 0 ? 1 : 0, width_i);
		ft_realloc(ret, 1, width_i);
		if (padding.f == &ft_strncat)
			width_i -= ft_strlen(*ret);
		if (**tmp == '-' || **tmp == '+')
			ft_offset_initialize(tmp, width_i, 1, padding);
		else if (**tmp != '\0')
			ft_offset_initialize(tmp, width_i, 2, padding);
		else
			ft_offset_initialize(tmp, width_i, 0, padding);
		(*tmp) = padding.f(*tmp, *ret, ft_strlen(*ret));
		free(*ret);
		*ret = *tmp;
	}
	else
		free(*tmp);
}

void		ft_write_padding_char(char **ret, t_opt *tab, t_padding padding,
		char **tmp)
{
	int		i;
	int		width_i;

	if ((i = ft_search_tab(tab, "width") >= 0)
			&& (width_i = tab[i].is_true) > (int)ft_strlen(*ret))
	{
		ft_realloc(tmp, 0, width_i);
		if (padding.f == &ft_strncat)
			width_i -= ft_strlen(*ret);
		if (**ret == '\0')
			width_i -= 1;
		*tmp = (char *)ft_memset((void *)(*tmp), padding.padding,
				(size_t)width_i);
		(*tmp)[width_i] = '\0';
		*tmp = padding.f(*tmp, *ret, ft_strlen(*ret) ? ft_strlen(*ret) : 1);
		free(*ret);
		if (!(**tmp) && width_i)
			(*tmp)[width_i] = ' ';
		*ret = *tmp;
	}
	else
		free(*tmp);
}

void		ft_write_padding_str(char **ret, t_opt *tab, t_padding padding,
		char **tmp)
{
	int		i;
	int		width_i;

	if ((i = ft_search_tab(tab, "width") >= 0)
			&& (width_i = tab[i].is_true) > (int)ft_strlen(*ret))
	{
		ft_realloc(tmp, 0, width_i);
		if (padding.f == &ft_strncat)
			width_i -= ft_strlen(*ret);
		*tmp = (char *)ft_memset((void *)(*tmp), padding.padding,
				(size_t)width_i);
		(*tmp)[width_i] = '\0';
		*tmp = padding.f(*tmp, *ret, ft_strlen(*ret));
		free(*ret);
		*ret = *tmp;
	}
	else
		free(*tmp);
}
