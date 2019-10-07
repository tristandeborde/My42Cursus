#ifndef LIBMEDIA_OPENGL_H
#define	LIBMEDIA_OPENGL_H
#include "libmedia_interface.hpp"

#include <GL/glew.h>

#if defined(__APPLE__)
# include <OpenGL/gl.h>
#else	// if defined(__APPLE__)
# include <GL/gl.h>
#endif	// if defined(__APPLE__)

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

typedef enum			e_model{
	WALL_MODEL,
	PLAYER_MODEL,
	BOMB_MODEL,
	FRUIT_MODEL,
	EXPLOSION_MODEL,
	FLOOR_MODEL,
	GROUND_MODEL,
	BUTTON_MODEL,
	SCORE_MODEL,
	WORLD_MODEL,
	SNAKE_HEAD_MODEL,
	SNAKE_LINE_MODEL,
	SNAKE_CORNER_MODEL,
	SNAKE_TAIL_MODEL
}						t_model;


#endif	// ifndef LIBMEDIA_OPENGL_H
