/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:57:41 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:15:32 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Verifie si la valeur int passé en parametre correspond à un caractere
** numerique.
*/

int		ft_isdigit(int c)
{
	return ((47 < c && c < 58) ? 1 : 0);
}
