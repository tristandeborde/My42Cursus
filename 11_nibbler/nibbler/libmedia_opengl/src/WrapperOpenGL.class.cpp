#include "WrapperOpenGL.class.hpp"
#include "Opengl.class.hpp"

WrapperOpenGL::WrapperOpenGL(void) = default;

WrapperOpenGL::~WrapperOpenGL(void) = default;

void WrapperOpenGL::libmedia_begin(void) {
	Opengl::get()->begin();
}

void WrapperOpenGL::libmedia_end(void) {
	Opengl::get()->end();
}

void WrapperOpenGL::libmedia_drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score) {
	Opengl::get()->drawgame(width, height, items, nb_items, score);
}

t_input	WrapperOpenGL::libmedia_input(void) {
	return Opengl::get()->input();
}

void WrapperOpenGL::libmedia_drawmenu(t_menu menu) {
	Opengl::get()->drawmenu(menu);
}

const char * WrapperOpenGL::libmedia_getlog(void) {
	return Opengl::get()->getlog();
}

extern "C" {
	ILibMedia * getLib() {
		return new WrapperOpenGL();
	}
}
