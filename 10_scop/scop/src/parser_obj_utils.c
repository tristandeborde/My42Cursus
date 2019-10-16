/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:59:39 by cmaxime           #+#    #+#             */
/*   Updated: 2019/09/25 17:00:17 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_parser.h"

int		ft_lstlen(t_list *list)
{
	int		len;

	len = 0;
	while (list)
	{
		++len;
		list = list->next;
	}
	return (len);
}

void	*ft_lstgetcontent(t_list *list, size_t pos)
{
	size_t		i;
	static char	trash[512];

	ft_bzero(trash, sizeof(trash));
	i = 0;
	while (list)
	{
		if (i == pos)
			return (list->content);
		++i;
		list = list->next;
	}
	return (trash);
}
