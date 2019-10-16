/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_initutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:26:13 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/08 12:28:22 by cmaxime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <errno.h>

int		init_window(t_opengl *opengl)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	opengl->window = glfwCreateWindow(1200, 1200, "Scop", NULL, NULL);
	if (opengl->window == NULL)
	{
		glfwTerminate();
		return (s_errmsg("Initiation failed : Window\n", -1));
	}
	glfwSetInputMode(opengl->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(opengl->window);
	glfwSetCursorPosCallback(opengl->window, &mouse_callback);
	glfwSetFramebufferSizeCallback(opengl->window, &framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (s_errmsg("Initiation failed : Glad\n", -1));
	glEnable(GL_DEPTH_TEST);
	return (0);
}

int		shader_setup(t_opengl *opengl)
{
	const char		*vertex_source;
	const char		*fragment_source;
	unsigned int	vertex;
	unsigned int	fragment;

	if (!(vertex_source = loadshaderfile("/shaders/vertex_shader.fs")))
		return (-1);
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_source, NULL);
	glCompileShader(vertex);
	free((void*)vertex_source);
	if (!(fragment_source = loadshaderfile("/shaders/fragment_shader.fs")))
		return (-1);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &(fragment_source), NULL);
	glCompileShader(fragment);
	free((void*)fragment_source);
	opengl->shader_program = glCreateProgram();
	glAttachShader(opengl->shader_program, vertex);
	glAttachShader(opengl->shader_program, fragment);
	glLinkProgram(opengl->shader_program);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return (0);
}

int		init_buffers(t_opengl *opengl, float *vertices, size_t len)
{
	glGenVertexArrays(1, &(opengl->vao));
	glBindVertexArray(opengl->vao);
	glGenBuffers(1, &(opengl->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, opengl->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * len, vertices,
			GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	return (0);
}

int		init_texture(t_opengl *opengl)
{
	int				width;
	int				height;
	unsigned char	*data;
	static char		real_path[512];

	ft_strcpy(real_path, BASEPATH);
	ft_strcat(real_path, "/assets/box.bmp");
	if (NULL == (data = readbmp_file(real_path, &width, &height)))
	{
		ft_printf("Initiation failed : Texture loading\n");
		return (-1);
	}
	glGenTextures(1, &(opengl->texture));
	glBindTexture(GL_TEXTURE_2D, opengl->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR,
			GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	free(data);
	return (0);
}

int		init_camera(void)
{
	t_camera *cam;

	if (NULL == (cam = getcam()))
		return (-1);
	cam->firstMouse = true;
	cam->yaw = -90.0f;
	cam->pitch = 0.0f;
	cam->lastX = 1200.0f / 2.0;
	cam->lastY = 1200.0 / 2.0;
	cam->cameraPos[0] = 0.0f;
	cam->cameraPos[1] = 0.0f;
	cam->cameraPos[2] = 3.0f;
	cam->cameraFront[0] = 0.0f;
	cam->cameraFront[1] = 0.0f;
	cam->cameraFront[2] = -1.0f;
	cam->cameraUp[0] = 0.0f;
	cam->cameraUp[1] = 1.0f;
	cam->cameraUp[2] = 0.0f;
	cam->deltaTime = 0.0f;
	cam->lastFrame = 0.0f;
	return (0);
}
