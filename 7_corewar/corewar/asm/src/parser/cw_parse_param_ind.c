/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse_param_ind.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:41:37 by pprikazs          #+#    #+#             */
/*   Updated: 2018/04/30 12:33:53 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_err.h"

static int		cw_parse_param_ind_aux(int i, char *param, \
		t_instruct *inst, int *pos)
{
	int			ret;

	ret = 1;
	if (param[*pos] == LABEL_CHAR)
	{
		ret = cw_parse_param_lab(i, &param[*pos], inst);
		(*pos)++;
	}
	return (ret);
}

extern int		cw_parse_param_ind(int i, char *param, t_instruct *inst)
{
	int			ret;
	int			pos;

	ret = 1;
	pos = 0;
	if ((ret = ((g_optab[inst->id].param[i] & T_IND) == T_IND)))
	{
		inst->ocp |= (IND_CODE << (6 - (2 * i)));
		if ((ret = cw_parse_param_ind_aux(i, param, inst, &pos)) < 0)
			return (ret);
		if ((inst->param[i].pid & T_LAB) == 0 &&
				!cw_parse_value(&(param[pos]), &(inst->param[i].val)))
			return (PROG_PARAM_ERR7);
		inst->param[i].pid |= T_IND;
	}
	else
		ret = PROG_PARAM_ERR8;
	return (ret);
}
