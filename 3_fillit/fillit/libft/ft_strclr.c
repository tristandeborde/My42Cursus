/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:30:09 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:42 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Remplace tout les caractere de la chaine passé en parametre par des '\0'
*/

void		ft_strclr(char *str)
{
	int i;

	i = 0;
	if (str != 0)
	{
		while (str[i] != '\0')
		{
			str[i] = '\0';
			i++;
		}
	}
}
