/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:45:12 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/07 20:26:43 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include "scop_math.h"
# include <stdio.h>

/*
** TO BE DELETED
*/
# include <cglm/mat4.h>
# include <cglm/cglm.h>

# include "glad/glad.h"
# include <GLFW/glfw3.h>


# define FALSE 0
# define TRUE 1
# define SCR_WIDTH 1200
# define SCR_HEIGHT 1200
# define SENSITIVITY 0.05f

typedef struct	s_opengl
{
	GLFWwindow	*window;
	uint32_t	vao;
	uint32_t	vbo;
	uint32_t	shader_program;
	uint32_t	texture;
}				t_opengl;

typedef struct 	s_camera
{
	bool firstMouse;
	float yaw;
	float pitch;
	float lastX;
	float lastY;
	t_vec3 cameraPos;
	t_vec3 cameraFront;
	t_vec3 cameraUp;
	t_vec3 moveForward;
	t_vec3 moveStrafe;
	float deltaTime;
	float lastFrame;
}				t_camera;


/*
** OpenGl functions
** obj.c
*/
int				init_opengl(t_opengl *opengl, float *vertices, size_t len);

char			*loadshaderfile(const char *path);

void			framebuffer_size_callback(GLFWwindow *window, int width,
		int height);
void			process_input(GLFWwindow *window, t_camera *cam);
int			s_errmsg(const char *msg, int ret);
void rotate(t_opengl *opengl, t_camera *cam);

/*
** OpenGL init utils
*/
int				init_camera(void);
int				init_texture(t_opengl *opengl);
int				init_buffers(t_opengl *opengl, float *vertices, size_t len);
int				shader_setup(t_opengl *opengl);
int				init_window(t_opengl *opengl);

/*
** OpenGL Utils
*/

void 			mouse_callback(GLFWwindow* window, double xpos, double ypos);
int		 		init_camera(void);
t_camera    	*getcam(void);


/*
** BMP loading functions
** bmp.c
*/
uint8_t			*readbmp_file(const char *path, int *width, int *height);


float   ft_rad(float angle);


#endif
