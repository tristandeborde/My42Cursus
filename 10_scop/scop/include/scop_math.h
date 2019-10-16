#ifndef SCOP_MATH_H
# define SCOP_MATH_H

typedef float	t_vec3[3];
typedef float	t_mat4[4][4];

#define MAT4_IDENTITY_INIT {{1.0f, 0.0f, 0.0f, 0.0f}, \
                        	{0.0f, 1.0f, 0.0f, 0.0f}, \
                        	{0.0f, 0.0f, 1.0f, 0.0f}, \
                        	{0.0f, 0.0f, 0.0f, 1.0f}}

void        ft_vec3_scale(t_vec3 src, float scale, t_vec3 dest);
void        ft_vec3_add(t_vec3 a, t_vec3 b, t_vec3 dest);
void        ft_vec3_sub(t_vec3 a, t_vec3 b, t_vec3 dest);
float       ft_vec3_dot(t_vec3 a, t_vec3 b);
float       ft_vec3_norm(t_vec3 v);
void        ft_vec3_normalize(t_vec3 v);
void        ft_vec3_normalize_to(t_vec3 src, t_vec3 dest);
void        ft_vec3_copy(t_vec3 a, t_vec3 dest);
void    	ft_vec3_cross(t_vec3 a, t_vec3 b, t_vec3 dest);
void    	ft_vec3_crossn(t_vec3 a, t_vec3 b, t_vec3 dest);
void 		ft_mat4_rotate(t_mat4 model, float angle, t_vec3 axis);
void    	ft_lookat(t_vec3 eye, t_vec3 center, t_vec3 up, t_mat4 dest);

#endif