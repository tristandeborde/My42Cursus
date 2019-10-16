#ifndef SCOP_PARSER_H
# define SCOP_PARSER_H

# ifndef BASEPATH
#  define BASEPATH ""
# endif

# define SPACE_CHAR	' '

# include <fcntl.h>

# include "libft.h"

typedef struct	s_obj
{
	t_list		*vertex;
	t_list		*normal;
	t_list		*texture;
	t_list		*face;
}				t_obj;

typedef struct	s_processor
{
	const char	*key;
	int			(*process)(t_obj*, char**);
}   			t_processor;

/*
** Object functions
** obj.c
*/
int				compile(t_obj *obj, float **vertices, size_t *len);

/*
** obj_utils.c
*/
void			*ft_lstgetcontent(t_list *list, size_t pos);
int				ft_lstlen(t_list *list);

/*
** Parser functions
** parser.c
*/
t_obj			*loadobj(const char *path);

/*
** parser_utils.c
*/
int				ft_isfloat(char *str);
int				ft_isint(char *str);
void			delobj(t_obj *obj);

/*
** parser_array.c
*/
float			*getvector(char **tab, size_t len);
int				*getface(char **tab, int index);

/*
** parser_fnctl.c
*/
int				addvertex(t_obj *obj, char **tab);
int				addnormal(t_obj *obj, char **tab);
int				addtexture(t_obj *obj, char **tab);
int				addface(t_obj *obj, char **tab);
int				pass(t_obj *obj, char **tab);


#endif