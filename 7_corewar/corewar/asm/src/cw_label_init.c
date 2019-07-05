/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_label_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:58:08 by cmaxime           #+#    #+#             */
/*   Updated: 2018/04/26 17:02:02 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		cw_get_addr_from_label(char *label, t_list *list)
{
	t_instruct	*inst;

	while (list)
	{
		inst = list->content;
		if (inst->label && ft_strcmp(inst->label, label) == 0)
			return (inst->pc);
		list = list->next;
	}
	return (-1);
}

int		cw_convert_to_addr(int val, int pc)
{
	int		result;

	if (val > pc)
		result = val - pc;
	else
		result = 0xffffffff - (pc - val - 1);
	return (result);
}

int		cw_check_label_instruct(t_instruct *inst, t_list *list)
{
	int		i;
	int		val;

	i = -1;
	while (++i < 3)
	{
		if (inst->param[i].link != NULL)
		{
			if ((val = cw_get_addr_from_label(inst->param[i].link, list)) != -1)
			{
				inst->param[i].val += cw_convert_to_addr(val, inst->pc);
				free(inst->param[i].link);
				inst->param[i].link = NULL;
			}
			else
				return (-1);
		}
	}
	return (1);
}

int		cw_check_duplicates_label(t_list *list)
{
	t_instruct	*inst;
	t_list		*buff;
	char		*label;

	while (list)
	{
		inst = list->content;
		if (inst->label)
		{
			buff = list->next;
			while (buff)
			{
				label = ((t_instruct*)(buff->content))->label;
				if (label && ft_strcmp(inst->label, label) == 0)
					return (-1);
				buff = buff->next;
			}
		}
		list = list->next;
	}
	return (1);
}

int		cw_label_init(t_list *list)
{
	int			ret;
	t_list		*cmd;
	t_instruct	*inst;

	ret = 0;
	cmd = list;
	while (cmd && ret != -1)
	{
		inst = cmd->content;
		ret = cw_check_label_instruct(inst, list);
		cmd = cmd->next;
	}
	return (ret);
}
