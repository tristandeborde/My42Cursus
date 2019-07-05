/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:22:52 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/30 13:10:43 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int			ft_search_tab(t_opt *tab, char *key)
{
	int i;

	i = -1;
	while (++i < 15)
	{
		if (!ft_strcmp(tab[i].sym, key) && tab[i].is_true)
			return (i);
	}
	return (-1);
}

void		ft_realloc(char **str, int is_dup, int width_i)
{
	char	*tmp;

	if (is_dup == 1)
		tmp = ft_strdup(*str);
	else
		tmp = ft_strnew(width_i + 1);
	free(*str);
	(*str) = tmp;
}

void		ft_offset_initialize(char **tmp, int width_i, int offset,
		t_padding padding)
{
	(*tmp) += offset;
	(*tmp) = (char *)ft_memset((void *)(*tmp), padding.padding,
			(size_t)width_i - offset);
	(*tmp)[width_i - offset] = '\0';
	(*tmp) -= offset;
}

void		ft_free_null(char **str)
{
	free(*str);
	*str = NULL;
}
