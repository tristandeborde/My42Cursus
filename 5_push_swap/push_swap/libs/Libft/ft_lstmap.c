/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 10:44:56 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/14 16:34:08 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*prev;
	t_list	*save;

	if (lst)
	{
		new = f(lst);
		save = new;
		lst = lst->next;
		while (lst)
		{
			prev = new;
			new = f(lst);
			prev->next = new;
			lst = lst->next;
		}
		return (save);
	}
	return (NULL);
}
