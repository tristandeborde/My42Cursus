/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse_param_dir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:38:24 by pprikazs          #+#    #+#             */
/*   Updated: 2018/04/30 12:29:29 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/cdefs.h>
#include "op.h"
#include "libft.h"
#include "asm.h"
#include "asm_err.h"

static int		cw_parse_param_dir_aux(int i, char *param, \
		t_instruct *inst, int *pos)
{
	int			ret;

	ret = 1;
	if (param[*pos] == 0)
		ret = PROG_PARAM_ERR2;
	else if (param[*pos] == LABEL_CHAR)
	{
		ret = cw_parse_param_lab(i, &param[*pos], inst);
		(*pos)++;
	}
	return (ret);
}

extern int		cw_parse_param_dir(int i, char *param, t_instruct *inst)
{
	int			ret;
	int			pos;

	ret = 1;
	pos = 1;
	if ((ret = ((g_optab[inst->id].param[i] & T_DIR) == T_DIR)))
	{
		inst->ocp |= (DIR_CODE << (6 - (2 * i)));
		if ((ret = cw_parse_param_dir_aux(i, param, inst, &pos)) < 0)
			return (ret);
		if ((inst->param[i].pid & T_LAB) == 0 &&
				!cw_parse_value(&(param[pos]), &(inst->param[i].val)))
			return (PROG_PARAM_ERR5);
		inst->param[i].pid |= T_DIR;
	}
	else
		ret = PROG_PARAM_ERR6;
	return (ret);
}
