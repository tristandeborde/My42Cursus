#ifndef ENTITY2D_STRUCT_HPP
#define	ENTITY2D_STRUCT_HPP

#include <SDL2/SDL.h>

struct Entity2D{
	/* Instantiation **************************************************************/
	Entity2D(float _x, float _y);

	/* Attributs ******************************************************************/
	float		  x {.0f};
	float		  y {.0f};
	SDL_Texture * texture {nullptr};
	SDL_Rect	  origin {};

	/* Compliant methods **********************************************************/
	Entity2D(void)	= default;
	~Entity2D(void) = default;
	Entity2D(const Entity2D &) = delete;
	Entity2D & operator=(const Entity2D &) = delete;
};

#endif	// ENTITY2D_STRUCT_HPP
