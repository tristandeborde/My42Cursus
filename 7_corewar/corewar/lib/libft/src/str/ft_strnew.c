/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 11:52:08 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/04/25 15:38:51 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *dst;

	if (!(dst = (char*)malloc(size + 1)))
		return (NULL);
	ft_bzero(dst, size + 1);
	return (dst);
}
