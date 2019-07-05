/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:27:00 by pprikazs          #+#    #+#             */
/*   Updated: 2017/11/30 14:27:54 by pprikazs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *str);
void			*ft_bzero(void *ptr, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isprint(int c);
int				ft_isupper(int c);
char			*ft_itoa(int nbr);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(const void *content, size_t content_size);
void			ft_lstpush_back(t_list **alst, t_list *new_one);
void			ft_lstpush_front(t_list **alst, t_list *new_one);
void			ft_lstpush_ultimate(t_list **alst, void *data, \
		size_t content_size, void (*f)(t_list **, t_list *));
int				ft_lstsize(t_list *begin_list);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *ptrd, const void *ptrs, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *ptrd, const void *ptrs, size_t n);
void			ft_memdel(void **ptr);
void			ft_memdel_size(void *content, size_t size);
int				ft_memjunc(void *ptr1, void *ptr2, size_t n);
void			*ft_memmove(void *ptrd, const void *ptrs, size_t n);
void			*ft_memset(void *ptr, int c, size_t n);
int				ft_next_sqrt(int nb);
int				ft_pow(int x, int y);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(const char *str);
void			ft_putendl_fd(const char *str, int fd);
void			ft_putnbr(int nbr);
void			ft_putnbr_fd(int nbr, int fd);
void			ft_putstr(const char *str);
void			ft_putstr_fd(const char *str, int fd);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *str, int c);
void			ft_strclr(char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
void			ft_strdel(char **str);
char			*ft_strdup(const char *s);
int				ft_strequ(const char *s1, const char *s2);
void			ft_striter(char *str, void (*f)(char *));
void			ft_striteri(char *str, void (*f)(unsigned int, char *));
char			*ft_strjoin(const char *s1, const char *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *str);
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *dest, const char *src, int nbr);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dest, const char *src, size_t n);
int				ft_strnequ(const char *s1, char const *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *str, const char *to_find, size_t n);
char			*ft_strrchr(const char *str, int c);
char			**ft_strsplit(const char *s, char c);
char			*ft_strstr(const char *str, const char *to_find);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strtrim(const char *s1);
void			ft_swap_uint(unsigned int *nb1, unsigned int *nb2);
int				ft_tolower(int c);
int				ft_toupper(int c);

#endif
