#include "Sdl.class.hpp"
#include "WrapperSDL2.class.hpp"

WrapperSDL2::WrapperSDL2(void) = default;

WrapperSDL2::~WrapperSDL2(void) = default;

void WrapperSDL2::libmedia_begin(void) {
	Sdl::get()->begin();
}

void WrapperSDL2::libmedia_end(void) {
	Sdl::get()->end();
}

void WrapperSDL2::libmedia_drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score) {
	Sdl::get()->drawgame(width, height, items, nb_items, score);
}

t_input	WrapperSDL2::libmedia_input(void) {
	return Sdl::get()->input();
}

void WrapperSDL2::libmedia_drawmenu(t_menu menu) {
	Sdl::get()->drawmenu(menu);
}

const char * WrapperSDL2::libmedia_getlog(void) {
	return Sdl::get()->getlog();
}

extern "C" {
	ILibMedia * getLib() {
		return new WrapperSDL2();
	}
}
