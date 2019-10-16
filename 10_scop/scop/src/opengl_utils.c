/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:54:43 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/08 16:37:31 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "scop_math.h"

void		framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

t_camera	*getcam(void)
{
	static t_camera *camera = NULL;

	if (camera == NULL)
		camera = (t_camera*)ft_memalloc(sizeof(t_camera));
	return (camera);
}

void		mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	t_camera	*cam;
	float		xoffset;
	float		yoffset;
	t_vec3		front;

	if (NULL == (cam = getcam()))
		return ;
	if (cam->firstMouse)
	{
		cam->lastX = xpos;
		cam->lastY = ypos;
		cam->firstMouse = false;
	}
	xoffset = xpos - cam->lastX;
	yoffset = cam->lastY - ypos;
	cam->lastX = xpos;
	cam->lastY = ypos;
	xoffset *= SENSITIVITY;
	yoffset *= SENSITIVITY;
	cam->yaw   += xoffset;
	cam->pitch += yoffset;  
	cam->pitch = cam->pitch > 89.0f ? 89.0f : cam->pitch;
	cam->pitch = cam->pitch < -89.0f ? -89.0f : cam->pitch;
	front[0] = cos(ft_rad(cam->pitch)) * cos(ft_rad(cam->yaw));
	front[1] = sin(ft_rad(cam->pitch));
	front[2] = cos(ft_rad(cam->pitch)) * sin(ft_rad(cam->yaw));
	ft_vec3_normalize(front);
	ft_vec3_copy(front, cam->cameraFront);
	(void)window;
}

void		rotate(t_opengl *opengl, t_camera *cam)
{
	float 			angle;
	unsigned int 	model_loc;
	unsigned int 	perspective_loc;
	unsigned int 	view_loc;

	t_mat4 model = MAT4_IDENTITY_INIT;
	angle = 20.0f * (float)glfwGetTime();
	t_vec3 rot_axes = {0.0f, 1.0f, 0.0f};
	ft_mat4_rotate(model, ft_rad(angle), rot_axes);
	t_mat4 perspective = MAT4_IDENTITY_INIT;
	glm_perspective(ft_rad(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f, perspective);
	t_mat4 view = MAT4_IDENTITY_INIT;
	t_vec3 cameraFrontNew;
	ft_vec3_add(cam->cameraFront, cam->cameraPos, cameraFrontNew);
	ft_lookat(cam->cameraPos, cameraFrontNew, cam->cameraUp, view);
	model_loc = glGetUniformLocation(opengl->shader_program, "model");
	perspective_loc = glGetUniformLocation(opengl->shader_program, "perspective");
	view_loc = glGetUniformLocation(opengl->shader_program, "view");
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float *)model);
	glUniformMatrix4fv(perspective_loc, 1, GL_FALSE, (float *)perspective);
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float *)view);
}
