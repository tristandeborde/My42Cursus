/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 18:50:32 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/01 10:28:42 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/cdefs.h>
#include "ft_printf.h"
#include "asm.h"

extern t_op		g_optab[OP_TAB_SIZE];

extern void		cw_display_g_optab(void)
{
	int			i;

	i = 0;
	while (i < OP_TAB_SIZE)
	{
		ft_printf("ins : %s | nb_param : %d | ", g_optab[i].ins, \
			g_optab[i].nb_param);
		ft_printf("params : {p1 %d , p2 %d, ", g_optab[i].param[0], \
			g_optab[i].param[1]);
		ft_printf("p3 %d, p4 %d} | ", g_optab[i].param[2], g_optab[i].param[3]);
		ft_printf("opcode : %d | ", g_optab[i].opcode);
		ft_printf("nb_cycle : %d | ", g_optab[i].nb_cycle);
		ft_printf("desc : %s | ", g_optab[i].desc);
		ft_printf("carry : %d | codage : %d \n", g_optab[i].carry, \
			g_optab[i].codage);
		i++;
	}
}

extern void		cw_display_header(t_header header)
{
	ft_putchar('\n');
	if (*(header.prog_name) != '\0')
	{
		ft_putstr("prog_name : ");
		ft_putendl(header.prog_name);
	}
	if (*(header.comment) != '\0')
	{
		ft_putstr("comment : ");
		ft_putendl(header.comment);
	}
}

/*
** Display d'un maillon de la list chainée contenant l'intégralité des
** instructions, après un premier formatage du fichier .s.
** Usage:
** 		ft_lstiter(instructs, &ft_display_instruct);
*/

extern void		cw_display_instruct(t_list *elem)
{
	t_instruct *content;

	content = ((t_instruct *)elem->content);
	ft_putstr("label : ");
	(content->label != 0) ? ft_putstr(content->label) : ft_putnbr(0);
	ft_printf(" | pc : %d | id : %d | ocp : ", content->pc, content->id);
	ft_putbit((void *)&(content->ocp), sizeof(unsigned char));
	ft_printf(" | params : link(%s) val(%d) pid(%d)", \
		content->param[0].link, content->param[0].val, content->param[0].pid);
	ft_printf(" | params : link(%s) val(%d) pid(%d)", \
		content->param[1].link, content->param[1].val, content->param[1].pid);
	ft_printf(" | params : link(%s) val(%d) pid(%d)\n", \
		content->param[2].link, content->param[2].val, content->param[2].pid);
}
