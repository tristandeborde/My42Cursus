/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:01:54 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:15:50 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Verifie si la valeur int passé en parametre correspond à une majuscule.
*/

int		ft_isupper(int c)
{
	return ((64 < c && c < 91) ? 1 : 0);
}