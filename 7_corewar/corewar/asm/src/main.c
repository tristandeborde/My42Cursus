/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:56:30 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/05/01 10:27:52 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			destroy_inst(t_list *list)
{
	t_list	*buff;

	while (list)
	{
		if (((t_instruct*)list->content)->label)
			free(((t_instruct*)list->content)->label);
		free(list->content);
		buff = list;
		list = list->next;
		free(buff);
	}
}

int				check_name_s(char *str)
{
	int		i;

	i = ft_strlen(str);
	if (i > 3 && str[i - 1] == 's' && str[i - 2] == '.')
		return (1);
	return (-30);
}

void			cw_display_usage(void)
{
	ft_putendl("Usage: ./asm [-ad] <sourcefile.s>");
	ft_putstr("    -a : Instead of creating a .cor file, outputs a stripped ");
	ft_putendl("and annotated version of the code to the standard output");
	ft_putendl("    -d  : Debug mode for more detailed error display");
}

int				cw_check_flags(int argc, char **argv, char *flags)
{
	int		i;
	int		j;

	i = 0;
	while (++i < argc - 1)
	{
		if (argv[i][0] == '-')
		{
			j = 0;
			while (argv[i][++j])
			{
				if (argv[i][j] == 'a' && (*flags & 0b01) == 0)
					*flags += 0b01;
				else if (argv[i][j] == 'd' && (*flags & 0b10) == 0)
					*flags += 0b10;
				else
					return (0);
			}
		}
		else
			return (0);
	}
	return (1);
}

int				main(int argc, char *argv[])
{
	t_list		*instruct;
	char		*bin;
	int			ret;
	t_header	head;
	char		flags;

	bin = NULL;
	flags = 0;
	if (argc > 1 && cw_check_flags(argc, argv, &flags))
	{
		if ((ret = check_name_s(argv[argc - 1])) > 0)
			ret = cw_parse(argv[argc - 1], &instruct, &head);
		if (ret > 0 && (ret = cw_prog_builder(instruct, &bin)) > 0)
		{
			head.magic = COREWAR_EXEC_MAGIC;
			head.prog_size = (unsigned int)ret;
			cw_write(argv[argc - 1], head, bin, ((flags & 0b01) != 0) ? 0 : 1);
		}
		else
			cw_error(ret, ft_lstlast(&instruct), ((flags & 0b10) != 0) ? 1 : 0);
		destroy_inst(instruct);
	}
	else
		cw_display_usage();
	return (0);
}
