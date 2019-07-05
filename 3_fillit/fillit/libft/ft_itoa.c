/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:16:15 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:15:54 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*malloc_strnbr(int nbr, int *size)
{
	char	*itoa;
	int		ope;

	ope = 1;
	if (nbr == 0)
		ope++;
	else if (nbr < 0)
		ope += 2;
	while ((nbr = nbr / 10) != 0)
		(*size)++;
	if ((itoa = (char *)malloc(sizeof(char) * (*size + ope))) == NULL)
		return (NULL);
	return (itoa);
}

static void		neg_solver(int *nbr, int *size, char *itoa, int *indice)
{
	if (*nbr < 0)
	{
		itoa[(*indice)++] = '-';
		if (*nbr == -2147483648)
		{
			itoa[(*indice)++] = '2';
			*nbr = *nbr % 1000000000;
			(*size)--;
		}
		*nbr = -(*nbr);
	}
}

extern char		*ft_itoa(int nbr)
{
	int		size;
	int		i;
	char	*itoa;

	i = 0;
	size = 0;
	if ((itoa = malloc_strnbr(nbr, &size)) == NULL)
		return (NULL);
	neg_solver(&nbr, &size, itoa, &i);
	size = ft_pow(10, size);
	while (size)
	{
		itoa[i++] = (nbr / size) + 48;
		nbr = nbr % size;
		size = size / 10;
	}
	itoa[i] = '\0';
	return (itoa);
}
