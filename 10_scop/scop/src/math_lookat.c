/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_lookat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:45:28 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/08 15:46:08 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_math.h"

void	ft_lookat(t_vec3 eye, t_vec3 center, t_vec3 up, t_mat4 dest)
{
	t_vec3 f;
	t_vec3 u;
	t_vec3 s;

	ft_vec3_sub(center, eye, f);
	ft_vec3_normalize(f);
	ft_vec3_crossn(f, up, s);
	ft_vec3_cross(s, f, u);
	dest[0][0] = s[0];
	dest[0][1] = u[0];
	dest[0][2] = -f[0];
	dest[1][0] = s[1];
	dest[1][1] = u[1];
	dest[1][2] = -f[1];
	dest[2][0] = s[2];
	dest[2][1] = u[2];
	dest[2][2] = -f[2];
	dest[3][0] = -ft_vec3_dot(s, eye);
	dest[3][1] = -ft_vec3_dot(u, eye);
	dest[3][2] = ft_vec3_dot(f, eye);
	dest[0][3] = 0.0f;
	dest[1][3] = 0.0f;
	dest[2][3] = 0.0f;
	dest[3][3] = 1.0f;
}
