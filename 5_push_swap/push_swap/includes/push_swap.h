/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:48:53 by tdeborde          #+#    #+#             */
/*   Updated: 2018/03/05 15:16:55 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define BUFF_SIZE 1
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct			s_file
{
	char				*buff;
}						t_file;

typedef struct			s_link
{
	intmax_t			num;
	int					ix;
	int					is_sorted;
	struct s_link		*next;
	struct s_link		*prev;
}						t_link;

typedef struct			s_instrucs
{
	char				*buff;
	struct s_instrucs	*next;
	struct s_instrucs	*prev;
}						t_instrucs;

typedef struct			s_piles
{
	t_link				*start_a;
	t_link				*start_b;
	t_link				*end_a;
	t_link				*end_b;
	t_instrucs			*instrucs_start;
	int					len_a;
	int					len_b;
}						t_piles;

typedef struct			s_ops_tab
{
	char				*op_name;
	void				(*op_func)(t_piles *piles, int display);
}						t_ops_tab;

int						ft_add_toplink(t_piles *piles, intmax_t num, int ix,
		char c);
int						ft_add_endlink(t_piles *piles, intmax_t num, int ix,
		char c);
int						ft_del_toplink(t_piles *piles, char c);
int						ft_check_dups(t_piles *piles, intmax_t num);
int						ft_check_instructions(char *str, t_ops_tab *o_tab);
int						ft_check_int(intmax_t nb);
int						ft_execute_instructions(char **instruc_tab,
		t_piles *piles,
		t_ops_tab *o_tab);
void					ft_freejoin(char **str1, char **str2);
char					**ft_get_instructions(t_ops_tab *o_tab, t_piles *piles);
void					ft_handle_error(void);
t_ops_tab				*ft_init_ops_tab(void);
t_piles					*ft_init_piles(void);
int						ft_isnumber(char *str);
int						ft_is_sorted(t_piles *piles);
void					ft_print_tab(t_piles *piles);
void					ft_print_piles(t_piles *piles);
t_piles					*ft_read_pile(int ac, char **av);
char					**ft_strtab_add(char **strtab, int len);
void					ft_sa(t_piles *piles, int display);
void					ft_sb(t_piles *piles, int display);
void					ft_ss(t_piles *piles, int display);
void					ft_pa(t_piles *piles, int display);
void					ft_pb(t_piles *piles, int display);
void					ft_ra(t_piles *piles, int display);
void					ft_rb(t_piles *piles, int display);
void					ft_rr(t_piles *piles, int display);
void					ft_rra(t_piles *piles, int display);
void					ft_rrb(t_piles *piles, int display);
void					ft_rrr(t_piles *piles, int display);
int						get_next_line(const int fd, char **str);
int						ft_pile_is_sorted(t_piles *piles, char pile,
		int median);
int						ft_pile_is_sorted_ascending(t_piles *piles, char pile,
		int median);
t_link					*ft_find_max(t_piles *piles, int limit);
void					ft_sort_piles(t_piles *piles);
void					ft_find_median_nb(int *medians_tab, int median);
int						ft_quick_path(t_link *link, t_piles *piles,
		char pile);
int						ft_has_median_a(t_piles *piles, int median, char pile,
		int limit);
int						ft_has_median_b1(t_piles *piles, int median);
int						ft_has_median_b2(t_piles *piles, int median,
		int limit);
void					ft_add_instruc(t_piles *piles, char *instruc);
int						ft_print_instrucs(t_piles *piles);
int						ft_selection_sort_a_end(t_piles *piles, char pile,
		int median, int lim);
int						ft_selection_sort_b(t_piles *piles, int median);
int						ft_selection_sort_a(t_piles *piles, char pile,
		int median);
void					ft_add_instruc(t_piles *piles, char *instruc);
void					ft_free_instrucs(t_piles *piles);
void					ft_free_instruc_tab(char **instruc_tab);
int						ft_replace_instrucs(t_instrucs *iter1,
		t_instrucs *iter2, char *buff);
int						ft_compare_instrucs(t_instrucs *iter1);
void					ft_optimize_instrucs(t_piles *piles);
void					ft_free_piles(t_piles *piles);
void					ft_find_local_min(t_link *iter, t_link **current_min,
		int median,
		t_link **start);
void					ft_organize_sorted_piles(t_piles *piles,
		t_link *current_min);
int						ft_quicksort(t_piles *piles, int pivot, int lim,
		char pile);
void					ft_stop_reading_instrucs(char *str, char **instruc_tab,
		t_piles *piles);
void					ft_free_input_tab(char ***tab, int ac);
char					***ft_get_pile_tab(int ac, char **av);
int						ft_check_params(char **tab, int j, intmax_t *num,
		t_piles *piles);
#endif
