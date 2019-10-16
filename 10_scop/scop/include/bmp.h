/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:56:52 by cmaxime           #+#    #+#             */
/*   Updated: 2019/09/26 17:03:27 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include "libft.h"
# include <fcntl.h>

# pragma pack(push, 1)

typedef struct	s_bmp_header
{
	uint16_t	type;
	uint32_t	size;
	uint16_t	reserved1;
	uint16_t	reserved2;
	uint32_t	offset;
	uint32_t	dib_header_size;
	int32_t		width;
	int32_t		height;
	uint16_t	colors_planes;
	uint16_t	bpp;
	uint32_t	compression;
	uint32_t	image_size_bytes;
	int32_t		h_resolution;
	int32_t		v_resolution;
	uint32_t	nb_colors;
	uint32_t	important_colors;
}				t_bmp_header;

# pragma pack(pop)

typedef struct	s_bmp_image
{
	t_bmp_header	header;
	uint8_t			*data;
}				t_bmp_image;

#endif
