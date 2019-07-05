/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:09:49 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/05/01 17:27:43 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <sys/cdefs.h>
# include <fcntl.h>
# include "libft.h"
# include "op.h"

typedef enum	e_bool
{
	FALSE = 0,
	TRUE = 1
}				t_bool;

# define OP_TAB_SIZE 17

typedef struct	s_op
{
	char		*ins;
	int8_t		nb_param;
	int8_t		param[4];
	int8_t		opcode;
	int			nb_cycle;
	char		*desc;
	t_bool		codage;
	t_bool		carry;
}				t_op;

typedef struct	s_param
{
	unsigned char	pid;
	int				val;
	char			*link;
}				t_param;

typedef struct	s_instruct
{
	char			*label;
	int				pc;
	int8_t			id;
	unsigned char	ocp;
	int				line;
	char			*data;
	t_bool			error;
	t_param			param[4];
}				t_instruct;

extern t_op		g_optab[OP_TAB_SIZE];

void			cw_display_optab(void);
void			cw_display_header(t_header header);
void			cw_display_instruct(t_list *elem);
void			cw_error(int err_code, t_list *last, int type);
int				cw_parse(char *file, t_list **instruct, t_header *head);
void			cw_parse_comment(char *line);
int				cw_parse_header(char *line, t_header *head);
int				cw_parse_instruct(char *instruct, t_instruct **inst, \
				char ***param);
int				cw_parse_label(char *line, t_instruct **inst, char ***lab);
int				cw_parse_param(t_instruct **ins, char **param);
int				cw_parse_param_dir(int i, char *param, t_instruct *inst);
int				cw_parse_param_ind(int i, char *param, t_instruct *inst);
int				cw_parse_param_lab(int i, char *param, t_instruct *inst);
int				cw_parse_param_reg(int i, t_instruct *inst, char *param);
void			cw_parse_update_pc(t_instruct **ins, t_list **list);
int				cw_parse_value(char *str, int *val);
char			cw_get_op(char *str);
void			cw_trim_line(char *str);
int				cw_end_header(char *str, int end);

/*
** fct max
*/
int				cw_prog_init(t_list *list, char **bin);
int				cw_check_duplicates_label(t_list *list);
int				cw_label_init(t_list *list);
int				cw_prog_builder(t_list *list, char **bin);

int				cw_write(char *name, t_header head, char *bin, int i);
void			cw_write_out(t_header head, char *bin);
char			*ft_cleaner(char *line);
void			cw_00101010_by_max(char *it_is_for_fun);

#endif
