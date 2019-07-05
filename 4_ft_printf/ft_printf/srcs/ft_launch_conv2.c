/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_conv2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 17:19:16 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/26 17:24:34 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void		ft_save_flag(t_opt *tab, char *str)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strnew(2);
	tmp[0] = *str;
	while (++i < 15)
	{
		if (!ft_strcmp(tab[i].sym, tmp))
			tab[i].is_true = 1;
		if (ft_strlen(tab[i].sym) > 1)
		{
			tmp[1] = *(str + 1);
			if (!ft_strcmp(tab[i].sym, tmp))
			{
				tab[i].is_true = 1;
				tab[i - 1].is_true = 0;
			}
			tmp[1] = '\0';
		}
	}
	free(tmp);
}

int			ft_return_len(char **ret, t_opt *tab, int i, char c)
{
	if (c == 'c' || c == 'C')
	{
		if ((i = ft_search_tab(tab, "width")) >= 0
				&& tab[i].is_true > (int)ft_strlen(*ret))
			return (tab[i].is_true);
		else
			return (ft_strlen(*ret) ? ft_strlen(*ret) : 1);
	}
	else
		return (ft_strlen(*ret));
}

char		*ft_find_type(t_opt *tab, t_type *types_tab,
		va_list args, char c)
{
	int				i;
	t_uf_convert	uf;
	t_f_convert		f;
	char			*ret;

	i = 0;
	ret = NULL;
	uf = NULL;
	f = NULL;
	while (!(ft_strchr(types_tab->sym, c)))
		types_tab++;
	ft_detect_long(tab, c, &uf, &f);
	(void)args;
	i = types_tab->conv(args, f, uf, &ret);
	if (ret)
		types_tab->ft_apply_options(&ret, tab, c, i);
	return (ret);
}
