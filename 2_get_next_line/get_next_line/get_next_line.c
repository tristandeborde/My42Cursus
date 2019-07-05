/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:11:04 by tdeborde          #+#    #+#             */
/*   Updated: 2017/12/11 10:55:56 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_reinit(char **str)
{
	char	*buff;
	char	*del;

	del = *str;
	buff = ft_strdup(*str);
	free(del);
	return (buff);
}

int		ft_strcchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	return (i);
}

int		ft_return_line(char **str, t_file *file)
{
	unsigned int	line_end;

	if ((file->buff)[0] != '\0')
	{
		line_end = ft_strcchr(*str, '\n');
		if ((*str)[line_end] == '\n')
		{
			(*str)[line_end] = '\0';
			*str = ft_str_reinit(str);
			ft_memmove(file->buff, file->buff + ft_strcchr(file->buff, '\n')
					+ 1, sizeof(char) * (BUFF_SIZE + 1));
		}
		else
			ft_memdel((void **)&(file->buff));
		return (1);
	}
	return (0);
}

int		fetch_next_line(char **str, t_file *file, const int fd)
{
	int					nbread;
	char				*tmp;

	nbread = 0;
	if (file->buff == NULL)
	{
		if (!(file->buff = (char *)ft_strnew(BUFF_SIZE + 1)) ||
			!(*str = (char *)ft_strnew(BUFF_SIZE)))
			return (0);
	}
	else
		*str = ft_strdup(file->buff);
	while (!(ft_strchr(file->buff, '\n'))
			&& (nbread = read(fd, file->buff, BUFF_SIZE)) > 0)
	{
		(file->buff)[nbread] = '\0';
		tmp = ft_strjoin(*str, file->buff);
		free(*str);
		*str = tmp;
	}
	if (nbread < 0)
		return (-1);
	return (ft_return_line(str, file));
}

int		get_next_line(const int fd, char **str)
{
	static t_file file[2147483647];

	if ((fd < 0) || !(str))
		return (-1);
	return (fetch_next_line(str, &(file[fd]), fd));
}
