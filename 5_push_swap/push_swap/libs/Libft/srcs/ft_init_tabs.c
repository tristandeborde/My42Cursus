/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:14:35 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/07 14:37:43 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_opt	*ft_init_opt_tab(void)
{
	int				i;
	static	t_opt	tab[15] = {
					{"precision", 0, NULL, NULL},
					{"width", 0, NULL, NULL},
					{"-", 0, NULL, NULL},
					{"0", 0, NULL, NULL},
					{"+", 0, NULL, NULL},
					{"#", 0, NULL, NULL},
					{".", 0, NULL, NULL},
					{"h", 0, &ft_process_short, &ft_process_ushort},
					{"hh", 0, &ft_process_shortshort, &ft_process_ushortshort},
					{"l", 0, &ft_process_long, &ft_process_ulong},
					{"ll", 0, &ft_process_longlong, &ft_process_ulonglong},
					{"j", 0, &ft_process_longlong, &ft_process_ulonglong},
					{"z", 0, &ft_process_sizet, &ft_process_usizet},
					{"base", 10, NULL, NULL},
					{" ", 0, NULL, NULL},
					};

	i = -1;
	while (++i < 15)
		tab[i].is_true = 0;
	tab[13].is_true = 10;
	return (tab);
}

t_type	*ft_init_type_tab(void)
{
	static t_type	tab[9] = {
					{"p", &ft_process_pointer, &ft_apply_options_uint},
					{"idD", &ft_process_int, &ft_apply_options_int},
					{"oO", &ft_process_octal, &ft_apply_options_uint},
					{"xX", &ft_process_hexa, &ft_apply_options_uint},
					{"Cc", &ft_process_char, &ft_apply_options_char},
					{"sS", &ft_process_str, &ft_apply_options_str},
					{"%", &ft_process_percent, &ft_apply_options_percent},
					{"uU", &ft_process_uint, &ft_apply_options_uint},
					};

	return (tab);
}
