/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_err.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:28:35 by pprikazs          #+#    #+#             */
/*   Updated: 2018/05/02 14:03:40 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ERR_H
# define ASM_ERR_H

# define ALLOC_ERR -1

# define FILE_NAME -30

# define PROG_HEADER_ERR1 -2
# define PROG_HEADER_ERR2 -3
# define PROG_HEADER_ERR3 -4
# define PROG_HEADER_ERR4 -5
# define PROG_HEADER_ERR5 -6
# define PROG_HEADER_ERR6 -7
# define PROG_HEADER_ERR7 -26
# define PROG_LABEL_ERR1 -8
# define PROG_LABEL_ERR2 -9
# define PROG_INS_ERR1 -10
# define PROG_INS_ERR2 -11
# define PROG_PARAM_ERR1 -12
# define PROG_PARAM_ERR2 -13
# define PROG_PARAM_ERR3 -14
# define PROG_PARAM_ERR4 -15
# define PROG_PARAM_ERR5 -16
# define PROG_PARAM_ERR6 -17
# define PROG_PARAM_ERR7 -18
# define PROG_PARAM_ERR8 -19
# define PROG_PARAM_ERR9 -20
# define PROG_PARAM_ERR10 -21
# define PROG_PARAM_ERR11 -22
# define PROG_PARAM_ERR12 -23
# define PROG_LABEL_ERR3 -24
# define PROG_LABEL_ERR4 -25
# define PROG_PARAM_EMPTY -27

/*
** PROG_PARAM_ERR2 -13 : Flag direct définit mais rien ne suit.
** PROG_PARAM_ERR3 -14 : Flag label définit mais rien ne suit
** PROG_PARAM_ERR4 -15 : Erreur de définition de label (caractere non accepté);
** PROG_PARAM_ERR5 -16 : Erreur de définition de paramettre direct
**							(caractere non accepté)
** PROG_PARAM_ERR6 -17 : Erreur l'instruction n'attend pas de paramettre
**							direct a cet emplacement
** PROG_PARAM_ERR7 -18 : Erreur de définition de paramettre indirect
**							(caractere non accepté)
** PROG_PARAM_ERR8 -19 : Erreur l'instruction n'attend pas de paramettre
**							indirect a cet emplacement
** PROG_PARAM_ERR9 -20 : Erreur Flag registre définit mais rien ne suit
** PROG_PARAM_ERR10 -21 : Erreur de définition de paramettre registre
**								(caractere non accepté)
** PROG_PARAM_ERR11 -22 : Erreur le paramettre n'attends pas de registe
**							à cet emplacement
** PROG_PARAM_ERR12 -23 : Erreur valeur de registre
** PROG_LABEL_ERR3 -24 : Duplicata de label
** PROG_LABEL_ERR4 -25 : Un label n'existe pas
*/

typedef struct		s_error
{
	int		err;
	char	*message;
}					t_error;

#endif
