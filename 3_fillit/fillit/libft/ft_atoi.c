/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:46:25 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:15:09 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Vérifie les carcatères spéciaux en début de chaine pour atoi.
*/

static const char		*checkspecial(const char *str)
{
	while (1)
	{
		if (*str == ' ' || *str == '\t' || *str == '\f' || *str == '\v' || \
				*str == '\r' || *str == '\n')
		{
			str++;
		}
		else
			break ;
	}
	return (str);
}

/*
** Tranforme la chaine de caractere numéric (si contenant des caracteres
** numérique) en un int et le retourn.
*/

extern int				ft_atoi(const char *str)
{
	int	neg;
	int	nbr;

	neg = 0;
	nbr = 0;
	str = checkspecial(str);
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		neg = 1;
	}
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			nbr = nbr * 10 - ((int)*str - '0');
		else
			return ((neg == 1) ? nbr : -nbr);
		str++;
	}
	return ((neg == 1) ? nbr : -nbr);
}
