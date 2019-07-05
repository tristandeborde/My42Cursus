/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 11:52:35 by blefeuvr          #+#    #+#             */
/*   Updated: 2018/05/01 09:57:50 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include "ft_printf.h"
# include <string.h>

/*
** get_next_line Paul
*/

# define MAX_FD 100
# define BUFF_SIZE 16384

typedef struct		s_buff
{
	char			*buff;
	int				cr;
}					t_buff;

/*
** end get_next_line Paul
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_ulist
{
	void			*content;
	size_t			content_size;
	struct s_ulist	*next;
	struct s_ulist	*prev;
}					t_ulist;

int					ft_isnum(char *str);
void				ft_putwchar_fd(wchar_t chr, int fd);
char				*ft_memjoin(char *s1, char *s2, size_t l1, size_t l2);
char				*ft_memsub(char *src, size_t start, size_t size);
char				*ft_memextend(char *dst, char *src, size_t sz_d, \
					size_t sz_s);
int					ft_cinstr(char c, char *str);
int					ft_gnl(int fd, char **line);
int					ft_max(int a, int b);
int					ft_min(int a, int b);
int					ft_pow(int a, int b);
intmax_t			ft_atoi_base_max(const char *str, int base);
int					ft_atoi_base(const char *str, const char *base);
size_t				ft_memclen(void *tab, char c);
void				ft_lstdelif(t_list **begin_list, void *content_ref, \
					int (*cmp)());
int					ft_abs(int a);
int					ft_strrepl(char *str, char from, char to);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isspace(char c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
char				*ft_itoa_base(uintmax_t n, char *base);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstaddend(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstlast(t_list **elem);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
int					ft_lstpush(t_list **alst, void *data, size_t content_size, \
					void (*f)(t_list **list, t_list *elem));
void				ft_lstpushb(t_list **alst, t_list *new_one);
void				ft_lstpushf(t_list **alst, t_list *new_one);
int					ft_lstsize(t_list *lst);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memcpy_x(void *ptrd, const void *ptrs, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memrealloc(void *ptr, size_t size, size_t org);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putbit(void *data, size_t n);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putcolor_24(const char *color, const char *str);
void				ft_putcolor_8(const char *color, const char *str);
void				ft_putcolor_hex24(long color, const char *str);
void				ft_putcolor_hex8(long color, const char *str);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
int					ft_sqrtup(int n);
char				*ft_strcat(char *s1, const char *s2);
int					ft_strccount(char *str, char c);
size_t				ft_strccpy(char *dst, char *src, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strchr(const char *s, int c);
size_t				ft_strclen(const char *dst, char c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
void				ft_strdel_tab(char **svg);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
char				**ft_strexplode(char const *s, char *c);
char				*ft_strextend(char *s1, char *s2);
char				*ft_strext(char *s1, char const *s2);
int					ft_strisdigit(const char *str);
int					ft_strisnumber(const char *str);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strndup(const char *s1, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *haystack, const char *needle, \
					size_t len);
char				*ft_strrchr(const char *s, int c);
void				ft_strsanitalize(char *str, const char *car);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_ulstadd_head(t_ulist **alst, t_ulist *new);
void				ft_ulstadd_tail(t_ulist **alst, t_ulist *new);
void				ft_ulstdel(t_ulist **alst, void (*del)(void*, size_t));
void				ft_ulstdelone(t_ulist **alst, void (*del)(void*, size_t));
t_ulist				*ft_ulstnew(void const *content, size_t content_size);
t_ulist				*ft_ulstset_head(t_ulist *alst);
t_ulist				*ft_ulstset_tail(t_ulist *alst);
size_t				ft_ulstsize(t_ulist *alst);
size_t				ft_ulsttsize(t_ulist *alst);
char				*ft_realloc(char *s1, char const *s2);

#endif
