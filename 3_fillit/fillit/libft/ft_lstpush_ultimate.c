/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_ultimate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:27:59 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/23 15:22:54 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush_ultimate(t_list **alst, void *data, size_t content_size, \
		void (*f)(t_list **, t_list *))
{
	if (*alst == 0)
		*alst = ft_lstnew(data, content_size);
	else
		f(alst, ft_lstnew(data, content_size));
}
