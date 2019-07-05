/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:52:19 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/29 16:06:13 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Cette fonction permet d'intervertir de valeur numérique si elle sont
** différentes.
*/

void			ft_swap_uint(unsigned int *nb1, unsigned int *nb2)
{
	unsigned int tmp;

	if (nb1 != nb2)
	{
		tmp = *nb1;
		*nb1 = *nb2;
		*nb2 = tmp;
	}
}
