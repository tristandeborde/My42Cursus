/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:51:51 by cmaxime           #+#    #+#             */
/*   Updated: 2019/10/07 20:25:43 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "scop.h"
#include "scop_parser.h"

/*
** https://fr.wikipedia.org/wiki/Objet_3D_(format_de_fichier)
*/

static void	verticesinfo(float *v, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len / 8)
	{
		printf("% 4.2f % 4.2f % 4.2f   % 4.2f % 4.2f   % 4.2f % 4.2f % 4.2f\n",
			(double)v[i * 8], (double)v[i * 8 + 1], (double)v[i * 8 + 2],
			(double)v[i * 8 + 3], (double)v[i * 8 + 4], (double)v[i * 8 + 5],
			(double)v[i * 8 + 6], (double)v[i * 8 + 7]);
		++i;
	}
}

static void	objinfo(t_obj *obj)
{
	t_list	*elem;
	float	*vect;
	int		*f;
	int		i;

	ft_printf("Vertex\n");
	elem = obj->vertex;
	while (NULL != elem)
	{
		vect = (float*)(elem->content);
		printf("[ % 7f, % 7f, % 7f ]\n", (double)vect[0], (double)vect[1], (double)vect[2]);
		elem = elem->next;
	}
	ft_printf("Normal\n");
	elem = obj->normal;
	while (NULL != elem)
	{
		vect = (float*)(elem->content);
		printf("[ % 7f, % 7f ]\n", (double)vect[0], (double)vect[1]);
		elem = elem->next;
	}
	ft_printf("Texture\n");
	elem = obj->texture;
	while (NULL != elem)
	{
		vect = (float*)(elem->content);
		printf("[ % 7f, % 7f, % 7f ]\n", (double)vect[0], (double)vect[1], (double)vect[2]);
		elem = elem->next;
	}
	ft_printf("Face\n");
	elem = obj->face;
	while (NULL != elem)
	{
		i = 0;
		while (i < 3)
		{
			f = (int*)(elem->content);
			ft_printf("(% 2d % 2d % 2d ) ", f[i * 3], f[i * 3 + 1], f[i * 3 + 2]);
			++i;
		}
		ft_printf("\n");
		elem = elem->next;
	}
}

/***********************************************************************/
/*************                   OPENGL                    *************/
/***********************************************************************/

static int	core(float *vertices, size_t len)
{
	t_opengl	opengl;
	t_camera	*cam;
	float currentFrame;

	if (-1 == init_opengl(&opengl, vertices, len))
		return (-1);

	cam = getcam();
	while(!glfwWindowShouldClose(opengl.window))
	{
		currentFrame = glfwGetTime();
		cam->deltaTime = currentFrame - cam->lastFrame;
		cam->lastFrame = currentFrame;
		process_input(opengl.window, cam);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(opengl.shader_program);
		glBindVertexArray(opengl.vao);

		rotate(&opengl, cam);
		glDrawArrays(GL_TRIANGLES, 0, len);

		glfwSwapBuffers(opengl.window);
		glfwPollEvents();    
	}

	free(cam);
	glDeleteVertexArrays(1, &(opengl.vao));
    glDeleteBuffers(1, &(opengl.vbo));

	glfwTerminate();
	return (0);
}

/***********************************************************************/
/*************                 END OPENGL                  *************/
/***********************************************************************/

static int	leaks_wrapper(int ac, char *av[])
{
	t_obj		*obj;
	float		*vertices;
	size_t		len;

	obj = NULL;
	vertices = NULL;
	len = 0;
	if (ac != 2 || NULL == (obj = loadobj(av[1])))
		ft_printf("ERROR\n");
	else
	{
		if (-1 == compile(obj, &vertices, &len))
			ft_printf("ERROR\n");
		// objinfo(obj);
		// verticesinfo(vertices, len);
		core(vertices, len);
		delobj(obj);
		free(vertices);
		ft_printf("OK\n");
	}
	return (0);
}

int			main(int ac, char *av[])
{
	int		ret;

	ret = leaks_wrapper(ac, av);
	return (0);
}
