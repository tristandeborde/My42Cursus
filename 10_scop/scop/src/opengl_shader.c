/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:56:21 by cmaxime           #+#    #+#             */
/*   Updated: 2019/09/26 16:56:29 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "scop.h"

char	*loadshaderfile(const char *path)
{
	int			fd;
	char		*shader;
	static char	*line = NULL;
	static char real_path[512];

	shader = NULL;
	ft_strcpy(real_path, BASEPATH);
	ft_strcat(real_path, path);
	if (-1 == (fd = open(real_path, O_RDONLY)))
	{
		ft_putendl(real_path);
		return (NULL);
	}
	while (get_next_line(fd, &line))
	{
		shader = ft_realloc(shader, line);
		shader = ft_realloc(shader, "\n");
		if (line)
			free(line);
	}
	return (shader);
}
