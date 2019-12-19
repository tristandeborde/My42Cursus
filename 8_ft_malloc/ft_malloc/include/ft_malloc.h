/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:41:20 by tdeborde          #+#    #+#             */
/*   Updated: 2019/06/13 12:27:43 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/mman.h>

# define BLK_NUMBER 100
# define TINY_SIZE 1024
# define MEDIUM_SIZE 4096

typedef	struct	s_blk
{
	size_t			size;
	struct s_blk	*next;
	uint32_t		is_free;
	char			pad[12];
}				t_blk;

pthread_mutex_t	g_mutex;
t_blk			*g_zones_table[3];

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			*calloc(size_t n, size_t size);
void			*malloc_engine(size_t size);
int				change_size(t_blk *blk, void *ptr2, size_t size);
void			handle_large(t_blk *blk);
void			show_alloc_mem(void);
t_blk			init_blk(size_t size);
t_blk			*alloc_blk(size_t size);
void			*handle_zones(size_t real_size, size_t size, int id);
void			ft_putunbr(size_t n);
void			ft_puthex(uintptr_t nb);
t_blk			*find_ptr(void *ptr);
int				print_blk_mem(t_blk *blk);
void			safe_memcpy(void *src, void *dest, size_t size1, size_t size2);

#endif
