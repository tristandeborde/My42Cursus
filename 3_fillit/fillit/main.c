/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:03:25 by tdeborde          #+#    #+#             */
/*   Updated: 2017/11/30 18:09:18 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"
#define RC ft_putchar('\n')

int		main(int ac, char **av)
{
	t_list	*list;
	t_list	*tetris;
	t_list	*coors;
	int		final_map_size;

	if (ac != 2)
		ft_display_usage();
	else if (ft_check_input(av, &list))
	{
		ft_parser_tetri(list, &tetris);
		ft_lstdel(&list, &ft_memdel_size);
		final_map_size = ft_backtracking(ft_next_sqrt(ft_lstsize(tetris) * 4), \
				tetris, &coors);
		ft_display_map(tetris, coors, final_map_size);
		ft_lstdel(&tetris, &ft_memdel_size);
		ft_lstdel(&coors, &ft_memdel_size);
	}
	else
		ft_putendl("error");
	return (0);
}
