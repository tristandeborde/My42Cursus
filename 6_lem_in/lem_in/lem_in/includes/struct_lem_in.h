/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lem_in.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 17:46:33 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/03/14 14:44:44 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_LEM_IN_H
# define STRUCT_LEM_IN_H

# include "libft.h"

typedef struct	s_link
{
	t_list	*node;
	int		val;
}				t_link;

typedef struct	s_node
{
	char	*id;
	int		x;
	int		y;
	int		status;
	int		dist;
	t_list	*link;
	int		link_count;
}				t_node;

typedef struct	s_path
{
	t_node	*node;
	int		len;
}				t_path;

typedef struct	s_data
{
	t_list	*node;
	t_list	*path;
	t_list	*best_path;
	char	*cmd;
	int		nb_ants;
	int		buff;
}				t_data;

typedef struct	s_parse
{
	t_data	(*f)(t_data data, int *status, char **line);
}				t_parse;

#endif
