/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse_param_lab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:45:45 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/01 09:55:16 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_err.h"

static int		cw_only_label(char *str, char **label)
{
	int		j;

	j = -1;
	ft_strsanitalize(str, "\t ");
	while (str[++j] != '\0')
	{
		if (!ft_strchr(LABEL_CHARS, str[j]))
			return (0);
	}
	*label = ft_strdup(str);
	return (1);
}

static int		cw_label_value(char *str, int *val, char **label)
{
	char	c;
	char	**tab;
	int		ret;
	int		j;

	if ((c = cw_get_op(str)) == '\0')
		return (cw_only_label(str, label));
	tab = ft_strsplit(str, c);
	ret = 1;
	ft_strsanitalize(tab[0], "\t ");
	ft_strsanitalize(tab[1], "\t ");
	j = -1;
	while (tab[0][++j] != '\0')
	{
		if (!ft_strchr(LABEL_CHARS, tab[0][j]))
			return (0);
	}
	*label = ft_strdup(tab[0]);
	if (!cw_parse_value(tab[1], val))
		ret = 0;
	ft_strdel_tab(tab);
	*val = (c == '-') ? *val * -1 : *val;
	return (ret);
}

extern int		cw_parse_param_lab(int i, char *param, t_instruct *inst)
{
	int		j;

	j = 0;
	if (param[1] == 0)
		return (PROG_PARAM_ERR3);
	if (!cw_label_value(param + 1, &(inst->param[i].val), \
		&(inst->param[i].link)))
		return (PROG_PARAM_ERR4);
	inst->param[i].pid |= (T_LAB);
	return (1);
}
