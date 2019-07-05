/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:43:04 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/05/02 10:56:23 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <limits.h>
# include <fcntl.h>
# include <stdint.h>
# include <unistd.h>
# include "libft.h"
# include "op.h"

# define DEBUG 1
# define BONUS 0
# define OP_TAB_SIZE 17
# define O_DIR 2
# define O_IND 3
# define O_REG 1

typedef struct		s_champion
{
	int				id;
	char			*name;
	char			*bin;
	int				size_prog;
}					t_champion;

typedef struct		s_process
{
	unsigned char	registries[REG_NUMBER][REG_SIZE];
	int				entrypoint;
	unsigned int	pc;
	int				carry;
	int				next_cycle;
	int				next_opcode;
	int				live;
	unsigned int	id;
}					t_process;

typedef struct		s_setting
{
	int				nbr_cycle;
	int				nbr_champion;
	t_champion		champion_tab[MAX_PLAYERS];
	int				time;
}					t_setting;

typedef struct		s_live
{
	int				index;
	unsigned int	cycle;
}					t_live;

typedef struct		s_loop
{
	int				cycle_to_die;
	int				next_cycle_to_die;
	int				next_max_check;
	t_live			last_live;
	int				nb_live;
}					t_loop;

typedef struct		s_vm
{
	t_setting		setting;
	int				cycle;
	t_list			*process;
	unsigned int	nb_process;
	unsigned char	*vm;
	t_loop			loop;
}					t_vm;

typedef enum		e_err
{
	ERR_UNKNOW,
	ERR_USAGE,
	ERR_MALLOC,
	ERR_PLAYER_NB
}					t_err;

typedef enum		e_bool
{
	FALSE = 0,
	TRUE = 1
}					t_bool;

typedef struct		s_op
{
	int				(*f)();
	int8_t			nb_param;
	int8_t			opcode;
	int				nb_cycle;
	t_bool			codage;
}					t_op;

extern t_op			g_optab[OP_TAB_SIZE];
extern t_op			g_op_tab[OP_TAB_SIZE];

int					cw_load_settings(t_setting *setting, int ac, char **av);
int					cw_load_champion(t_setting *setting, char *file, int i, \
					int id);
void				cw_init_setting(t_setting *setting);
int					cw_init_dump(t_setting *setting, int ac, char **av);
int					cw_init_champion(t_setting *setting, int ac, char **av, \
					int i);
int					cw_init_champion_id(t_setting *setting);
int					cw_check_champion_id(t_setting *setting, int id);
char				*cw_read_champion_header(int fd, int *size);
char				*cw_read_champion_prog(int fd, char *bin, int prog_size, \
					int *size);
int					cw_check_bin_header(char *bin);
int					cw_check_bin_null(char *bin, int pos);
void				cw_load_bin_champion(t_champion *champ, char *bin, \
					int size, int id);
int					cw_strisdig(char *str);
int					cw_check_cor_file(char *file);
void				cw_exec_process(t_vm *vm, t_process *process);
int					cw_error_custom(char *str);
void				cw_create_process(t_vm *vm);
void				cw_vm_init(t_vm *vm, int ac, char **av);
void				cw_error(int err);
void				cw_core_loop(t_vm vm);
void				cw_process_process(t_vm *vm, int cycle);
void				cw_check_process(t_vm *vm, int max);
void				cw_dump_and_quit(t_vm *vm);
void				cw_game_over(t_vm *vm);
char				*cw_itoa_base(char n, char *base);
t_champion			*cw_find_player(t_setting *setting, int index);
int					cw_live(t_vm *vm, t_process *process);
int					cw_ld(t_vm *vm, t_process *process);
int					cw_st(t_vm *vm, t_process *process);
int					cw_sti(t_vm *vm, t_process *process);
int					cw_and(t_vm *vm, t_process *process);
int					cw_zjump(t_vm *vm, t_process *process);
int					cw_add(t_vm *vm, t_process *process);
int					cw_sub(t_vm *vm, t_process *process);
int					cw_or(t_vm *vm, t_process *process);
int					cw_xor(t_vm *vm, t_process *process);
int					cw_ldi(t_vm *vm, t_process *process);
int					cw_fork(t_vm *vm, t_process *process);
int					cw_lld(t_vm *vm, t_process *process);
int					cw_lldi(t_vm *vm, t_process *process);
int					cw_lfork(t_vm *vm, t_process *process);
int					cw_aff(t_vm *vm, t_process *process);
int					cw_get_1(unsigned char *vm);
int					cw_get_2(unsigned char *vm);
int					cw_get_4(unsigned char *vm);
int					cw_get_int(unsigned char *vm, int off, int len);
int					cw_check_reg(int param);
void				cw_rev_get(unsigned char *registries, int nb);
int					cw_read_ocp(t_vm *vm, t_process *process, int *param, \
					unsigned char ocp_trunc);
int					cw_read_ocp_short(t_vm *vm, t_process *process, int *param,\
					unsigned char ocp_trunc);
void				cw_wait_process(t_vm *vm, t_process *process);
int					cw_ocp_offset(unsigned char ocp_trunc, int is_short, \
					int nb);
void				*cw_memcpy_to_circle(void *dst, void *src, int off, \
					int len);
void				*cw_memcpy_from_circle(void *dst, void *src, int off, \
					int len);
void				cw_dump_all(t_vm *vm);

#endif
