/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:00:18 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/15 12:33:27 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_interlink(t_link *link1, t_link *link2)
{
	link1->next = link2;
	link2->prev = link1;
}

static int	*ft_init_link_val(t_piles *piles, t_link ***start, t_link ***end,
		char c)
{
	(*start) = c == 'a' ? &(piles->start_a) : &(piles->start_b);
	(*end) = c == 'a' ? &(piles->end_a) : &(piles->end_b);
	return (c == 'a' ? &(piles->len_a) : &(piles->len_b));
}

int			ft_add_toplink(t_piles *piles, intmax_t num, int ix, char c)
{
	t_link	*new_start;
	t_link	**old_start;
	t_link	**end;
	int		*len;

	len = ft_init_link_val(piles, &old_start, &end, c);
	if (!(new_start = (t_link *)ft_memalloc(sizeof(t_link))))
		ft_handle_error();
	new_start->num = num;
	new_start->ix = ix;
	if (!(*len))
	{
		ft_interlink(new_start, new_start);
		(*end) = new_start;
	}
	else
	{
		ft_interlink(new_start, (*old_start));
		ft_interlink((*end), new_start);
	}
	(*old_start) = new_start;
	(*len)++;
	return (1);
}

int			ft_add_endlink(t_piles *piles, intmax_t num, int ix, char c)
{
	t_link	*new_end;
	t_link	**start;
	t_link	**old_end;
	int		*len;

	len = ft_init_link_val(piles, &start, &old_end, c);
	if (!(new_end = (t_link *)ft_memalloc(sizeof(t_link))))
		ft_handle_error();
	new_end->num = num;
	new_end->ix = ix;
	if (!(*len))
	{
		ft_interlink(new_end, new_end);
		(*start) = new_end;
	}
	else
	{
		ft_interlink(new_end, (*start));
		ft_interlink((*old_end), new_end);
	}
	(*old_end) = new_end;
	(*len)++;
	return (1);
}

int			ft_del_toplink(t_piles *piles, char c)
{
	t_link	*old_start;
	t_link	**new_start;
	t_link	**end;
	int		*len;

	len = ft_init_link_val(piles, &new_start, &end, c);
	if (!(*new_start))
		return (0);
	if ((*len) == 1)
	{
		free(*new_start);
		*new_start = NULL;
		*end = NULL;
	}
	else
	{
		old_start = (*new_start);
		(*new_start) = (*new_start)->next;
		free(old_start);
		(*new_start)->prev = (*end);
		if (*end)
			(*end)->next = (*new_start);
	}
	(*len)--;
	return (1);
}
