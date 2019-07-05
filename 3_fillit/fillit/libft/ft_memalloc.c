/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:23:30 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:16:44 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *tmp;

	if (size > 4294967295)
		return (NULL);
	if ((tmp = (void *)malloc(size)) == NULL)
		return (NULL);
	return (ft_bzero(tmp, size));
}
