/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 10:48:24 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/26 11:26:50 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_offset_sign(char **nb, char sign)
{
	char	*tmp;

	tmp = ft_strnew(ft_strlen(*nb));
	*tmp = sign;
	(tmp)++;
	ft_strcpy(tmp, *nb);
	free(*nb);
	*nb = --(tmp);
}

void		ft_place_sign(t_opt *tab, t_padding padding, char **ret, char **tmp)
{
	char	sign;
	int		i;

	sign = '+';
	i = 0;
	if ((i = ft_search_tab(tab, "base")) >= 0 &&
			ft_atoi_base(*ret, tab[i].is_true) < 0)
	{
		sign = '-';
		i = 0;
		while ((*ret)[i] != '-')
			i++;
		if (i > 0)
			(*ret)[i] = (ft_search_tab(tab, ".") >= 0) ? '0' : padding.padding;
		else
			ft_memmove(&(**ret), &(*((*ret) + 1)),
					ft_strlen(&(*((*ret) + 1))) + 1);
	}
	i = 0;
	if (padding.padding == '0' && (i = ft_search_tab(tab, "width")) >= 0
			&& (tab[i].is_true > (int)ft_strlen(*ret)))
		**tmp = sign;
	else
		ft_offset_sign(ret, sign);
}

void		ft_apply_hashtag(char **ret, t_padding padding, char **tmp,
		t_opt *tab)
{
	char	*tmp2;
	int		i;

	i = 0;
	if (padding.padding == '0' && (i = ft_search_tab(tab, "width"))
			&& tab[i].is_true > (int)ft_strlen(*ret) + 1 && *tmp)
		*tmp = ft_strcpy(*tmp, padding.hashtag);
	else if (*tmp)
	{
		tmp2 = ft_strnew(ft_strlen(*ret) + ft_strlen(padding.hashtag) + 1);
		tmp2 = ft_strcpy(tmp2, padding.hashtag);
		tmp2 += ft_strlen(padding.hashtag);
		tmp2 = ft_strcpy(tmp2, *ret);
		tmp2 -= ft_strlen(padding.hashtag);
		free(*ret);
		*ret = tmp2;
	}
}

int			ft_apply_space(char **ret, t_opt *tab)
{
	char	*tmp2;
	int		i;

	i = -1;
	if (**ret == ' ')
		return (0);
	else if (**ret == '0' && (*((*ret) + 1)) != 'x'
			&& ft_search_tab(tab, ".") == -1
			&& (i = ft_search_tab(tab, "width")) >= 0
			&& tab[i].is_true == (int)ft_strlen(*ret))
		**ret = ' ';
	else if ((*((*ret) + 1)) != 'x')
	{
		tmp2 = ft_strjoin(" ", *ret);
		free(*ret);
		*ret = tmp2;
	}
	return (1);
}
