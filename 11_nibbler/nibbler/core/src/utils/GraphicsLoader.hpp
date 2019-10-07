#ifndef GRAPHICS_LOADER_HPP
#define	GRAPHICS_LOADER_HPP

#ifndef BASEPATH

// not a constexpr value because it can be changed at compilation threw the -D flag
# define	BASEPATH "./"

#endif	// #ifndef BASEPATH

#include "libmedia_interface.hpp"

enum class eGraphicsType{
	LIBMEDIA_NCURSES,
	LIBMEDIA_SDL2,
	LIBMEDIA_OPENGL
};

namespace GraphicsLoader
{
	void load(eGraphicsType);
	void	end(void);

	void	libmedia_drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score);
	void	libmedia_drawmenu(t_menu menu);
	t_input	libmedia_input(void);
}// namespace GraphicsLoader

#endif	// GRAPHICS_LOADER_HPP
