/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse_param_reg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:46:50 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/01 15:20:08 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/cdefs.h>
#include "op.h"
#include "libft.h"
#include "asm.h"
#include "asm_err.h"

extern int		cw_parse_param_reg(int i, t_instruct *inst, char *param)
{
	int		ret;

	if ((ret = ((g_optab[inst->id].param[i] & T_REG) == T_REG)))
	{
		if (param[1] == '\0')
			return (PROG_PARAM_ERR9);
		if (!ft_strisdigit(&(param[1])))
			return (PROG_PARAM_ERR10);
		inst->param[i].val = ft_atoi(&(param[1]));
		if (inst->param[i].val < 0 || 99 < inst->param[i].val)
			return (PROG_PARAM_ERR12);
		inst->param[i].pid |= T_REG;
		inst->ocp |= (REG_CODE << (6 - (2 * i)));
	}
	else
		ret = PROG_PARAM_ERR11;
	return (ret);
}
