/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:24:10 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/27 18:24:32 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Alloue une chaine de caractere fraiche remplie de \0
*/

char		*ft_strnew(size_t size)
{
	char	*str;

	if ((str = (char *)(ft_memalloc(sizeof(char) * size + 1))) == 0)
		return (0);
	return (str);
}
