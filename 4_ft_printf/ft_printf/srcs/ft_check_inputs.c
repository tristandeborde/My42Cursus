/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:18:38 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/26 11:08:33 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_check_options(char **format)
{
	(*format)++;
	if (!(**format))
		return (0);
	while ((**format) && (ft_strchr("-+0# hljz.", **format)
				|| ft_isdigit(**format)))
		(*format)++;
	if ((**format) && ft_strchr("sSpdDioOuUxXcC%", **format))
		return (1);
	else if ((**format) && !ft_strchr("sSpdDioOuxXcC%-+0# hljz0123456789",
				**format))
		return (2);
	else
		return (0);
}
