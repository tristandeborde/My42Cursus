/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:50:55 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/02 14:01:02 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_err.h"

t_error			*get_error_t(void)
{
	static t_error	tab[18] = {
		{ALLOC_ERR, "Allocation error"},
		{PROG_HEADER_ERR1, ".name is defined twice"},
		{PROG_HEADER_ERR2, "No .name defined"},
		{PROG_HEADER_ERR3, ".name is to long (128 char max)"},
		{PROG_HEADER_ERR4, ".comment is defined twice"},
		{PROG_HEADER_ERR5, ".comment is too long (2046 char max)"},
		{PROG_HEADER_ERR6, ".name/.comment not defined"},
		{PROG_HEADER_ERR7, ".comment not defined"},
		{PROG_LABEL_ERR1, "Syntax error, line start with ':'"},
		{PROG_LABEL_ERR2, "Syntax error, bad caracter in 'label'"},
		{PROG_INS_ERR1, "No instructions in the program"},
		{PROG_INS_ERR2, "Instruction not existing"},
		{PROG_PARAM_ERR1, "Bad number of parameters for the instruction"},
		{PROG_LABEL_ERR3, "Label declared twice"},
		{PROG_LABEL_ERR4, "Label not existing"},
		{FILE_NAME, "Bad file extention, should be *.s"},
		{PROG_PARAM_EMPTY, "Empty param or too many ','"},
		{0, NULL}
	};

	return (tab);
}

t_error			*get_error_p(void)
{
	static t_error	tab[12] = {
		{PROG_PARAM_ERR2, "DIR flag defined but no value"},
		{PROG_PARAM_ERR3, "LABEL flag defined with no value"},
		{PROG_PARAM_ERR4, "LABEL contain forbidden caracter"},
		{PROG_PARAM_ERR5, "DIR contain forbidden carater"},
		{PROG_PARAM_ERR6, "Bad DIR param for instruction"},
		{PROG_PARAM_ERR7, "IND contain forbidden value"},
		{PROG_PARAM_ERR8, "Bad IND param for instruction"},
		{PROG_PARAM_ERR9, "REG flag defined with no value"},
		{PROG_PARAM_ERR10, "REG contain bad caracter"},
		{PROG_PARAM_ERR11, "Bad REG param for instruction"},
		{PROG_PARAM_ERR12, "Bad REG value must be between 1 to 16"},
		{0, NULL}
	};

	return (tab);
}

static void		cw_normal_error(t_list *last)
{
	(void)last;
	ft_putcolor_hex24(0xffffff, "Error while attempting to compile");
}

extern void		cw_error(int err_code, t_list *last, int type)
{
	t_error		*err_tab;
	int			i;

	if (type == 1)
	{
		err_tab = (err_code < -12 && err_code > -24) ? \
			get_error_p() : get_error_t();
		i = -1;
		while (err_tab[++i].message)
		{
			if (err_code == err_tab[i].err)
			{
				ft_putcolor_hex24(0xdd0025, err_tab[i].message);
				break ;
			}
		}
		if (err_tab[i].message == NULL)
			cw_normal_error(last);
		if (last)
			ft_printf(" at line: %d", ((t_instruct*)last->content)->line);
	}
	else
		cw_normal_error(last);
	ft_putendl(".");
}
