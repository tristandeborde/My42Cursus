/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:13:05 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/02 13:47:26 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/cdefs.h>
#include "op.h"
#include "libft.h"
#include "asm.h"
#include "asm_err.h"

static void		cw_init_param(t_instruct *inst, int i)
{
	inst->param[i].pid = 0;
	inst->param[i].val = 0;
	inst->param[i].link = 0;
}

static int		cw_count_param(char **param)
{
	int			i;

	i = 0;
	while (param[i] != '\0')
		i++;
	return (i);
}

static int		cw_insert_param(char *param, t_instruct **inst, int i)
{
	int			ret;

	ret = 1;
	if (param != 0)
		ft_strsanitalize(param, "\t ");
	if (param == 0)
		return (ret);
	if (ret > 0 && param[0] == 'r')
		ret = cw_parse_param_reg(i, *inst, param);
	else if (ret > 0 && param[0] == DIRECT_CHAR)
		ret = cw_parse_param_dir(i, param, *inst);
	else if (ret > 0)
		ret = cw_parse_param_ind(i, param, *inst);
	return (ret);
}

extern int		cw_parse_param(t_instruct **inst, char **param)
{
	int		nb_param;
	int		ret;
	int		i;

	if (param == 0)
		return (1);
	if ((nb_param = cw_count_param(param)) != g_optab[(*inst)->id].nb_param)
		return (PROG_PARAM_ERR1);
	i = 0;
	ret = 1;
	while (i < MAX_ARGS_NUMBER && ret >= 0)
	{
		if (i < nb_param)
		{
			cw_init_param(*inst, i);
			if ((ret = cw_insert_param(param[i], inst, i)) <= 0)
				break ;
		}
		else
			ret = cw_insert_param(0, inst, i);
		i++;
	}
	return (ret);
}
