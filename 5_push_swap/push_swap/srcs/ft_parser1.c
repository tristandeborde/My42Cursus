/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:29:29 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/15 12:34:10 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_add_instruc(t_piles *piles, char *instruc)
{
	t_instrucs	*new;
	t_instrucs	*iter;

	if (!(new = (t_instrucs *)ft_memalloc(sizeof(t_instrucs))))
		ft_handle_error();
	new->buff = ft_strdup(instruc);
	new->next = NULL;
	new->prev = NULL;
	if (piles->instrucs_start)
	{
		iter = piles->instrucs_start;
		while (iter->next)
			iter = iter->next;
		iter->next = new;
		new->prev = iter;
	}
	else
		piles->instrucs_start = new;
}

void		ft_free_instrucs(t_piles *piles)
{
	t_instrucs	*iter;
	t_instrucs	*iter2;

	iter = piles->instrucs_start;
	while (iter)
	{
		iter2 = iter;
		iter = iter->next;
		free(iter2->buff);
		free(iter2);
	}
}

int			ft_replace_instrucs(t_instrucs *iter1, t_instrucs *iter2,
		char *buff)
{
	free(iter1->buff);
	free(iter2->buff);
	if (!buff)
	{
		iter1->prev->next = iter2->next;
		free(iter1);
		free(iter2);
		return (-1);
	}
	else if (ft_strlen(buff) > 3)
	{
		iter1->buff = ft_strndup(buff, 2);
		iter1->next = iter2->next;
		iter2->next->prev = iter1;
		free(iter2->next->buff);
		iter2->next->buff = ft_strndup(&(buff[2]), 2);
	}
	else
	{
		iter1->buff = ft_strdup(buff);
		iter1->next = iter2->next;
	}
	free(iter2);
	return (1);
}

int			ft_compare_instrucs(t_instrucs *iter1)
{
	t_instrucs	*iter2;

	if (!(iter2 = iter1->next))
		return (0);
	if ((!ft_strcmp(iter1->buff, "ra") && !ft_strcmp(iter2->buff, "rb")) ||
			(!ft_strcmp(iter1->buff, "rb") && !ft_strcmp(iter2->buff, "ra")))
		return (ft_replace_instrucs(iter1, iter2, "rr"));
	else if ((!ft_strcmp(iter1->buff, "rra") && !ft_strcmp(iter2->buff, "rrb"))
		|| (!ft_strcmp(iter1->buff, "rrb") && !ft_strcmp(iter2->buff, "rra")))
		return (ft_replace_instrucs(iter1, iter2, "rrr"));
	else if (iter2 && iter2->next && ((!ft_strcmp(iter1->next->buff, "pa")
					&& !ft_strcmp(iter2->next->buff, "pb"))
		|| (!ft_strcmp(iter1->next->buff, "pb")
			&& !ft_strcmp(iter2->next->buff, "pa"))))
		return (ft_replace_instrucs(iter1->next, iter2->next, NULL));
	else if (!ft_strcmp(iter1->buff, "ra") && !ft_strcmp(iter2->buff, "pb") &&
			!ft_strcmp(iter2->next->buff, "rra"))
		return (ft_replace_instrucs(iter1, iter2, "sapb"));
	else if ((!ft_strcmp(iter1->buff, "rb") && !ft_strcmp(iter2->buff, "pa") &&
			!ft_strcmp(iter2->next->buff, "rrb")))
		return (ft_replace_instrucs(iter1, iter2, "sbpa"));
	else
		return (0);
}

void		ft_optimize_instrucs(t_piles *piles)
{
	t_instrucs	*iter1;
	int			i;

	i = 0;
	iter1 = piles->instrucs_start;
	while (iter1)
	{
		if (!ft_compare_instrucs(iter1))
			iter1 = iter1->next;
		i++;
	}
}
