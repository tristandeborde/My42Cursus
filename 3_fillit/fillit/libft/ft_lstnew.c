/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:42:56 by adleau            #+#    #+#             */
/*   Updated: 2017/11/15 13:16:41 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*lst;

	if ((lst = (t_list *)ft_memalloc(sizeof(t_list))) == 0)
		return (0);
	if (content)
	{
		lst->content = ft_memalloc(sizeof(unsigned char) * content_size);
		if (lst->content)
		{
			ft_memcpy(lst->content, content, content_size);
			lst->content_size = content_size;
		}
	}
	else
	{
		lst->content = 0;
		lst->content_size = 0;
	}
	lst->next = 0;
	return (lst);
}
