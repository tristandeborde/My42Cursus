/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:29:42 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:23:44 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	char			*str_alias;

	i = 0;
	str_alias = b;
	while (i < len)
	{
		str_alias[i] = (char)c;
		i++;
	}
	return (b);
}
