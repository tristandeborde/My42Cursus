/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:46:32 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/23 14:29:12 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstpush_back(t_list **alst, t_list *new_one)
{
	if (alst)
	{
		if ((*alst)->next != NULL)
			ft_lstpush_back(&(*alst)->next, new_one);
		else
			(*alst)->next = new_one;
	}
}
