#include "WrapperNcurses.class.hpp"
#include "Renderer.class.hpp"

WrapperNcurses::WrapperNcurses(void) {
	this->renderer = nullptr;
}

WrapperNcurses::~WrapperNcurses(void) = default;

void WrapperNcurses::libmedia_begin() {
	this->renderer = new Renderer();
}

void WrapperNcurses::libmedia_end() {
	delete this->renderer;
	this->renderer = nullptr;
}

void WrapperNcurses::libmedia_drawgame(
  size_t   width,
  size_t   height,
  t_item * items,
  size_t   nb_items,
  uint32_t score) {
	this->renderer->drawgame(width, height, items, nb_items, score);
}

void WrapperNcurses::libmedia_drawmenu(
  t_menu menu) {
	this->renderer->drawmenu(menu);
}

t_input	WrapperNcurses::libmedia_input(void) {
	return this->renderer->input();
}

const char * WrapperNcurses::libmedia_getlog(void) {
	return this->renderer->getlog();
}

extern "C"
{
	ILibMedia * getLib(void) {
		return new WrapperNcurses();
	}
}
