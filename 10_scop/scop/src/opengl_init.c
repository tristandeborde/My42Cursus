/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:37:35 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/07 20:28:11 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			s_errmsg(const char *msg, int ret)
{
	ft_printf(msg);
	return (ret);
}

int			init_opengl(t_opengl *opengl, float *vertices, size_t len)
{
	ft_bzero(opengl, sizeof(t_opengl));
	if (-1 == init_window(opengl))
		return (s_errmsg("Initiation failed : Opengl\n", -1));
	if (-1 == shader_setup(opengl))
		return (s_errmsg("Initiation failed : Shader\n", -1));
	if (-1 == init_buffers(opengl, vertices, len))
		return (s_errmsg("Initiation failed : Buffers\n", -1));
	if (-1 == init_texture(opengl))
		return (s_errmsg("Initiation failed : Textures\n", -1));
	if (-1 == init_camera())
		return (s_errmsg("Initiation failed : Camera\n", -1));
	return (0);
}
