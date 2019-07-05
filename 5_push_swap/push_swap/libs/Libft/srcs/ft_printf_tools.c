/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 17:28:08 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/07 14:38:02 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_copy_char(char **str, char **final_str, int len)
{
	char			tmp;
	char			*tmp2;

	tmp = (*str)[1];
	(*str)[1] = '\0';
	if (!(*final_str))
		*final_str = ft_strsub(*str, 0, 1);
	else
	{
		tmp2 = *final_str;
		*final_str = ft_strnjoin(*final_str, *str, len, 1);
		free(tmp2);
	}
	(*str)[1] = tmp;
	return (1);
}

int				ft_handle_noret(char **final_str, int *len_save,
		char **tmp, char **ret)
{
	if (*final_str)
	{
		*len_save = !(*len_save) && !(*final_str) ? 1 : *len_save;
		if (*len_save)
			ft_putbytes(ft_strsub(*final_str, 0, *len_save),\
					*len_save);
		free(*final_str);
	}
	free(*tmp);
	(void)*ret;
	return (-1);
}
