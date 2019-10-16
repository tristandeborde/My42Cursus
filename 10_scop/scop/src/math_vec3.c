/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:46:22 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/08 15:46:38 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_math.h"

void	ft_vec3_scale(t_vec3 src, float scale, t_vec3 dest)
{
	dest[0] = src[0] * scale;
	dest[1] = src[1] * scale;
	dest[2] = src[2] * scale;
}

void	ft_vec3_add(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
}

void	ft_vec3_sub(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
}

void	ft_vec3_copy(t_vec3 a, t_vec3 dest)
{
	dest[0] = a[0];
	dest[1] = a[1];
	dest[2] = a[2];
}
