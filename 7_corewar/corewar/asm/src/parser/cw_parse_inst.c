/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_inst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:12:37 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/02 14:01:01 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_err.h"

static int8_t	cw_isset_instruct(char *instruct)
{
	int			i;

	i = 0;
	while (i < OP_TAB_SIZE - 1)
	{
		if (!ft_strcmp(instruct, g_optab[i].ins))
			return (g_optab[i].opcode - 1);
		i++;
	}
	return (-1);
}

static void		cw_clear_first_param(char *fparam)
{
	int			i;
	int			y;

	i = 0;
	y = 0;
	while (!ft_strchr(" ", fparam[y]))
		y++;
	while (fparam[y] != '\0')
	{
		fparam[i] = fparam[y];
		i++;
		y++;
	}
	fparam[i] = '\0';
}

static int		cw_count_char(char **tab, char *str, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i - 1 == count ? 1 : 0);
}

extern int		cw_parse_instruct(char *instruct, t_instruct **inst, \
		char ***param)
{
	int8_t		id;
	char		**ins;

	ft_strsanitalize(instruct, "\t ");
	ins = ft_strsplit(instruct, ' ');
	if (ins == 0)
		return (PROG_INS_ERR1);
	if ((id = cw_isset_instruct(ins[0])) == -1)
	{
		ft_strdel_tab(ins);
		return (PROG_INS_ERR2);
	}
	ft_strdel_tab(ins);
	(*inst)->id = id;
	if (((*param) = ft_strsplit(instruct, SEPARATOR_CHAR)) == 0)
		return (ALLOC_ERR);
	if (cw_count_char(*param, instruct, SEPARATOR_CHAR) == 0)
		return (PROG_PARAM_EMPTY);
	cw_clear_first_param(**param);
	return (1);
}
