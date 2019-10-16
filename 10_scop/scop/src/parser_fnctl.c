/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fnctl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:09:33 by cmaxime           #+#    #+#             */
/*   Updated: 2019/09/25 14:10:25 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_parser.h"

int		addvertex(t_obj *obj, char **tab)
{
	float	*vect;
	t_list	*elem;

	if (NULL == (vect = getvector(tab, 3)))
		return (-1);
	if (NULL == (elem = ft_lstnew(vect, sizeof(float) * 3)))
	{
		free(vect);
		return (-1);
	}
	free(vect);
	ft_list_pushback(&(obj->vertex), elem);
	return (0);
}

int		addnormal(t_obj *obj, char **tab)
{
	float	*vect;
	t_list	*elem;

	if (NULL == (vect = getvector(tab, 2)))
		return (-1);
	if (NULL == (elem = ft_lstnew(vect, sizeof(float) * 2)))
	{
		free(vect);
		return (-1);
	}
	free(vect);
	ft_list_pushback(&(obj->normal), elem);
	return (0);
}

int		addtexture(t_obj *obj, char **tab)
{
	float	*vect;
	t_list	*elem;

	if (NULL == (vect = getvector(tab, 3)))
		return (-1);
	if (NULL == (elem = ft_lstnew(vect, sizeof(float) * 3)))
	{
		free(vect);
		return (-1);
	}
	free(vect);
	ft_list_pushback(&(obj->texture), elem);
	return (0);
}

int		pass(t_obj *obj, char **tab)
{
	(void)obj;
	(void)tab;
	return (0);
}
