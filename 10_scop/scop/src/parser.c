/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:53:59 by cmaxime           #+#    #+#             */
/*   Updated: 2019/09/25 14:13:41 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "scop_parser.h"

static int			process_row(t_obj *obj, char *line)
{
	int					i;
	char				**tmp;
	static t_processor	ind[6] = {
		{"v", &addvertex}, {"vt", &addnormal}, {"vn", &addtexture},
		{"o", &pass}, {"f", &addface}, {"g", &pass}};

	tmp = ft_strsplit(line, SPACE_CHAR);
	if (NULL == tmp[0] || line[0] == '#')
	{
		ft_deltab(tmp);
		return (0);
	}
	i = -1;
	while ((size_t)(++i) < sizeof(ind) / sizeof(char*))
	{
		if (0 == ft_strcmp(tmp[0], ind[i].key))
		{
			ind[i].process(obj, tmp);
			break ;
		}
	}
	if (i == sizeof(ind) / sizeof(char*))
		ft_printf("Bad\n");
	ft_deltab(tmp);
	return (0);
}

t_obj				*loadobj(const char *path)
{
	int			fd;
	t_obj		*obj;
	static char	*line = NULL;

	obj = NULL;
	if (NULL == (obj = (t_obj*)ft_memalloc(sizeof(t_obj))))
		return (NULL);
	if (-1 == (fd = open(path, O_RDONLY)))
		return (NULL);
	while (get_next_line(fd, &line))
	{
		if (NULL != line && -1 == process_row(obj, line))
		{
			delobj(obj);
			return (NULL);
		}
		if (NULL != line)
			free(line);
	}
	return (obj);
}
