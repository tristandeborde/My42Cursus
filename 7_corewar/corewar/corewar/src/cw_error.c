/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 09:12:56 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/28 15:46:53 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_error(int err)
{
	static const char *error[] = {
		"Error: unknown",
		"usage: ./corewar [-dump nb] [-t nb] [-n nb] champion1.cor ...",
		"Error: malloc failed"
	};

	ft_putendl_fd(error[err], 2);
	exit(1);
}

int		cw_error_custom(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}
