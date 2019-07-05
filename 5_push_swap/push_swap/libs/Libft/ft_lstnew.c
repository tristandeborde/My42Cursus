/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:26:51 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:24:32 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_one;

	if (!(new_one = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!(content) ||
			!(new_one->content = (void *)malloc(sizeof(void) * content_size)))
	{
		new_one->content_size = 0;
		new_one->content = NULL;
	}
	else
	{
		ft_memcpy(new_one->content, (void *)content, content_size);
		new_one->content_size = content_size;
	}
	new_one->next = NULL;
	return (new_one);
}
