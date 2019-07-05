/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_write_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 13:44:17 by cmaxime           #+#    #+#             */
/*   Updated: 2018/05/02 11:27:56 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	cw_write_uint_out(unsigned int magic, int *j)
{
	char	c;
	int		i;

	i = 0;
	while (i < 4)
	{
		c = (char)(magic >> ((3 - i) * 8));
		*j += 1;
		ft_printf("%02hhx ", c);
		if (*j % 16 == 0)
			ft_printf("\n%#0.3x :  ", *j);
		i++;
	}
}

void	cw_write_str_out(char *str, int size, int *j)
{
	int		i;
	char	c;

	c = 0;
	i = -1;
	while (++i < (int)ft_strlen(str))
	{
		*j += 1;
		ft_printf("%02hhx ", str[i]);
		if (*j % 16 == 0)
			ft_printf("\n%#0.3x :  ", *j);
	}
	while (i++ < size)
	{
		*j += 1;
		ft_printf("%02hhx ", c);
		if (*j % 16 == 0)
			ft_printf("\n%#0.3x :  ", *j);
	}
}

void	cw_write_null_out(int size, int *j)
{
	int		i;
	char	c;

	c = 0;
	i = 0;
	while (i++ < size)
	{
		*j += 1;
		ft_printf("%02hhx ", c);
		if (*j % 16 == 0)
			ft_printf("\n%#0.3x :  ", *j);
	}
}

void	cw_write_prog_out(char *str, int size, int *j)
{
	int		i;
	char	c;

	c = 0;
	i = -1;
	while (++i < size)
	{
		*j += 1;
		ft_printf("%02hhx ", str[i]);
		if (*j % 16 == 0)
			ft_printf("\n%#0.3x :  ", *j);
	}
}

void	cw_write_out(t_header h, char *bin)
{
	int		j;

	j = 0;
	ft_putstr("Expected output for .cor file !\n\n0x000 :  ");
	cw_write_uint_out(h.magic, &j);
	h.prog_name[ft_strlen(h.prog_name) - 1] = '\0';
	h.comment[ft_strlen(h.comment) - 1] = '\0';
	cw_write_str_out(h.prog_name, PROG_NAME_LENGTH, &j);
	cw_write_null_out(4, &j);
	cw_write_uint_out(h.prog_size, &j);
	cw_write_str_out(h.comment, COMMENT_LENGTH, &j);
	cw_write_null_out(4, &j);
	cw_write_prog_out(bin, h.prog_size, &j);
}
