/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec3_complex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:46:49 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/08 16:46:57 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_math.h"
#include <math.h>

float	ft_vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

float	ft_vec3_norm(t_vec3 v)
{
	return (sqrtf(ft_vec3_dot(v, v)));
}

void	ft_vec3_normalize(t_vec3 v)
{
	float norm;

	norm = ft_vec3_norm(v);
	if (norm == 0.0f)
	{
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		return ;
	}
	ft_vec3_scale(v, 1.0f / norm, v);
}

void    ft_vec3_normalize_to(t_vec3 src, t_vec3 dest)
{
    float norm;

    norm = ft_vec3_norm(src);
    if (norm == 0.0f)
    {
        dest[0] = 0.0f;
        dest[1] = 0.0f;
        dest[2] = 0.0f;
        return ;
    }
    ft_vec3_scale(src, 1.0f / norm, dest);
}

void    ft_vec3_crossn(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	ft_vec3_cross(a, b, dest);
	ft_vec3_normalize(dest);
}

void	ft_vec3_cross(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[1] * b[2] - a[2] * b[1];
	dest[1] = a[2] * b[0] - a[0] * b[2];
	dest[2] = a[0] * b[1] - a[1] * b[0];
}
