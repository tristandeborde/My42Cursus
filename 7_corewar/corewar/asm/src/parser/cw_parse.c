/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:40:26 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/16 17:39:26 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_err.h"

static int		cw_dest_aux(char **tab, int ret)
{
	ft_strdel_tab(tab);
	return (ret);
}

static int		cw_parse_line_aux(char *line, t_list **list, t_instruct **ins)
{
	char		**instruct;
	char		**param;
	int			ret;

	instruct = 0;
	param = 0;
	(void)list;
	if ((ret = cw_parse_label(line, ins, &instruct)) < 0)
		return (ret);
	if (ret == 1)
	{
		if (*(instruct[1]) == '\0')
			return (cw_dest_aux(instruct, 1));
		else if ((ret = cw_parse_instruct(instruct[1], ins, &param)) < 0)
			return (cw_dest_aux(instruct, ret));
	}
	else if (ret == 0 && (ret = cw_parse_instruct(line, ins, &param)) < 0)
		return (ret);
	if ((ret = cw_parse_param(ins, param)) < 0)
		return (ret);
	if (instruct != 0)
		ft_strdel_tab(instruct);
	if (param != 0)
		ft_strdel_tab(param);
	return (1);
}

static int		cw_parse_line(char *line, t_list **list, t_header *head, \
		int line_nb)
{
	t_instruct	*ins;
	int			ret;

	cw_parse_comment(line);
	if ((ret = cw_parse_header(line, head)) <= 0 || ret == 2)
		return (ret);
	cw_trim_line(line);
	if (*line == '\0')
		return (1);
	ft_strsanitalize(line, "\t ");
	line = ft_cleaner(line);
	if (!(ins = (t_instruct *)ft_memalloc(sizeof(t_instruct))))
		return (ALLOC_ERR);
	ins->id = OP_TAB_SIZE - 1;
	ins->line = line_nb;
	ret = cw_parse_line_aux(line, list, &ins);
	cw_parse_update_pc(&ins, list);
	ft_lstpush(list, (void *)ins, sizeof(t_instruct), &ft_lstpushb);
	ft_memdel((void**)&ins);
	return (ret);
}

static int		cw_final_check(t_list *list)
{
	if (cw_check_duplicates_label(list) == -1)
		return (PROG_LABEL_ERR3);
	if (cw_label_init(list) == -1)
		return (PROG_LABEL_ERR4);
	return (1);
}

extern int		cw_parse(char *file, t_list **list, t_header *head)
{
	int			fd;
	int			ret;
	char		*line;
	int			line_nb;

	ret = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	*list = 0;
	line_nb = 0;
	line = 0;
	*(head->comment) = '\0';
	*(head->prog_name) = '\0';
	while (ft_gnl(fd, &line) > 0 && ret >= 0)
	{
		line_nb++;
		ret = cw_parse_line(line, list, head, line_nb);
		ft_strdel((char **)&line);
	}
	if (line)
		ft_strdel((char **)&line);
	if (ret <= 0)
		return (ret);
	return (cw_final_check(*list));
}
