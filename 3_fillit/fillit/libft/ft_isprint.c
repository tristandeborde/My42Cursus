/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:59:16 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:15:47 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Verifie si la valeur int passé en parametre correspond à un caractere
** imprimable.
*/

int		ft_isprint(int c)
{
	return ((31 < c && c < 127) ? 1 : 0);
}
