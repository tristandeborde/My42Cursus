/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:21:56 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:45 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Comprare les deux chaine de caractere passé en parametre, retourne null (0)
** si les 2 chaine sont identiques sinon, une valeur non null.
*/

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] - s2[i] != '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
