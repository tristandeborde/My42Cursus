/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 09:45:33 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/05/01 09:40:43 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelif(t_list **begin_list, void *content_ref, int (*cmp)())
{
	t_list	*buff;
	t_list	*list;

	list = *begin_list;
	while (list && cmp(list->content, content_ref) == 0)
	{
		buff = list;
		*begin_list = list->next;
		free(buff->content);
		free(buff);
		list = *begin_list;
	}
	while (list && list->next)
	{
		if (cmp(list->next->content, content_ref) == 0)
		{
			buff = list->next;
			list->next = list->next->next;
			free(buff->content);
			free(buff);
		}
		else if (list->next)
			list = list->next;
	}
}
