/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 17:05:42 by cmaxime           #+#    #+#             */
/*   Updated: 2019/09/26 17:06:02 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

uint8_t	*readbmp_file(const char *path, int *width, int *height)
{
	int			fd;
	int			ret;
	t_bmp_image	img;

	if (-1 == (fd = open(path, O_RDONLY)))
		return (NULL);
	ret = read(fd, &(img.header), sizeof(t_bmp_header));
	if (NULL == (img.data = (uint8_t*)ft_memalloc(sizeof(uint8_t) *
					img.header.image_size_bytes)))
		return (NULL);
	if (0 > (ret = read(fd, img.data, img.header.image_size_bytes)))
	{
		free(img.data);
		return (NULL);
	}
	*width = img.header.width;
	*height = img.header.height;
	return (img.data);
}
