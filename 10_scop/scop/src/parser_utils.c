/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:10:30 by cmaxime           #+#    #+#             */
/*   Updated: 2019/09/25 14:11:46 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_parser.h"

int				ft_isfloat(char *str)
{
	size_t	i;
	int		dot;

	i = 0;
	dot = 0;
	if (str[0] == '-')
		i++;
	while ('\0' != str[i])
	{
		if (1 != dot && str[i] == '.')
			dot = 1;
		else if (1 != ft_isdigit(str[i]))
			return (-1);
		++i;
	}
	return (0);
}

int				ft_isint(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while ('\0' != str[i])
	{
		if (1 != ft_isdigit(str[i]))
			return (-1);
		++i;
	}
	return (0);
}

static void		delelem(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
}

void			delobj(t_obj *obj)
{
	delelem(obj->vertex);
	delelem(obj->normal);
	delelem(obj->texture);
	delelem(obj->face);
	free(obj);
}
