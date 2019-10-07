#ifndef RENDERERMANAGER_CLASS_HPP
#define	RENDERERMANAGER_CLASS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "libmedia_sdl2.h"

#include <map>
#include <utility>
#include <deque>

#include "Entity2D.struct.hpp"

/* Typedefs *******************************************************************/
using t_ipos	  = std::pair<int32_t, int32_t>;
using item_list_t = std::deque<Entity2D *>;
using item_map_t  = std::multimap<t_ipos, t_item>;

class RendererManager
{
	private:
		static RendererManager * _inst;

	/* Instantiation **************************************************************/
	public:
		static RendererManager * get(void);

	public:
		void         begin(void);
		void        end(void);

		SDL_Window * getWindow(void) const;
		SDL_Renderer * getRenderer(void) const;

		/* Methods ********************************************************************/
		void update(void) const;
		void resetWindow(void);
		void resetWindow(const SDL_Color &color);

		item_list_t bind(item_map_t map) const;
		void draw(item_list_t list, size_t w, size_t h) const;

		SDL_Rect getBoxShape(size_t w, size_t h) const;
		SDL_Rect getButtonShape(size_t nb_button) const;
		void updateColor(const SDL_Color &color) const;

	/* Attributes *****************************************************************/
	private:
		SDL_Window * _window {nullptr};
		SDL_Renderer * _renderer {nullptr};
		int _window_height {0};
		int _window_width {0};

	/* Coplien methods ************************************************************/
	private:
		RendererManager(void) = default;

	public:
		~RendererManager(void) = default;
		RendererManager(const RendererManager&) = delete;
		RendererManager& operator=(const RendererManager&) = delete;
};


#endif	// #ifndef RENDERERMANAGER_CLASS_HPP
