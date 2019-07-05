/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:29:49 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/30 14:33:42 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (*alst)
	{
		ft_lstdel(&((*alst)->next), del);
		del((void *)(*alst)->content, (*alst)->content_size);
		ft_memdel((void **)alst);
	}
}
