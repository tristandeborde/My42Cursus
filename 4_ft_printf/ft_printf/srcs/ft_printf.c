/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:33:00 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/26 17:28:45 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static t_format	*ft_init_format(const char *format)
{
	static t_format		f[1];

	f->final_str = NULL;
	f->str = ft_strdup(format);
	f->tmp = f->str;
	f->len = 0;
	f->ret = NULL;
	f->len_save = 0;
	return (f);
}

static int		ft_handle_flag(t_format *f, va_list args)
{
	char	*tmp2;

	f->len_tmp = ft_read_flag(f->str, args, &(f->ret));
	if ((f->len_tmp) < 0
			&& ft_handle_noret(&(f->final_str), &(f->len_save),
				&(f->tmp), &(f->ret)) < 0)
		return (-1);
	if (!(f->final_str))
		f->final_str = ft_strndup(f->ret, f->len_tmp + 1);
	else
	{
		tmp2 = f->final_str;
		f->final_str = ft_strnjoin(f->final_str, f->ret, f->len, f->len_tmp);
		free(tmp2);
	}
	if (f->ret)
		free(f->ret);
	f->len_save = f->len + f->len_tmp;
	return (1);
}

static void		ft_handle_falseflag(t_format *f, va_list args)
{
	char	*tmp2;

	f->len_tmp = ft_read_flag_noconv(f->str, args, &(f->ret), *(f->str));
	if (!(f->final_str))
		f->final_str = ft_strndup(f->ret, f->len_tmp);
	else
	{
		tmp2 = f->final_str;
		f->final_str = ft_strnjoin(f->final_str, f->ret, f->len, f->len_tmp);
		free(tmp2);
	}
	f->len_save = f->len + f->len_tmp;
	free(f->ret);
}

static int		ft_endvalues(t_format *f)
{
	if (!(f->final_str))
		return (0);
	if (f->tmp)
		free(f->tmp);
	free(f->final_str);
	return (f->len);
}

int				ft_printf(const char *format, ...)
{
	va_list			args;
	t_format		*f;
	int				i;

	va_start(args, format);
	f = ft_init_format(format);
	i = 0;
	while (*(f->str))
	{
		f->len_tmp = 0;
		if (*(f->str) != '%')
			f->len_tmp = ft_copy_char(&(f->str), &(f->final_str), f->len);
		else if ((i = ft_check_options(&(f->str))) == 1
				&& (ft_handle_flag(f, args) < 0))
			return (-1);
		else if (i == 2)
			ft_handle_falseflag(f, args);
		f->len += f->len_tmp;
		(f->str)++;
	}
	ft_putbytes(f->final_str, f->len);
	va_end(args);
	return (ft_endvalues(f));
}
