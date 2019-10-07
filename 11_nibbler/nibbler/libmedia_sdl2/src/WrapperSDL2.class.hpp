#ifndef WRAPPERSDL2_CLASS_HPP
#define	WRAPPERSDL2_CLASS_HPP

class Renderer;

#include "libmedia_interface.hpp"

class WrapperSDL2: public ILibMedia {
	/* Instantiation **************************************************************/
	public:
		WrapperSDL2(void);
		~WrapperSDL2(void) override;

	/* WrapperSDL2 Methods *********************************************************/
	public:
		void         libmedia_begin(void) override;
		void         libmedia_end(void) override;
		void         libmedia_drawgame(size_t width, size_t height, t_item * items, size_t nb_items,
			uint32_t score) override;
		void         libmedia_drawmenu(t_menu menu) override;
		t_input      libmedia_input(void) override;
		const char * libmedia_getlog(void) override;

	/* Coplien Methods ************************************************************/
	public:
		WrapperSDL2(WrapperSDL2 const &src) = delete;
		WrapperSDL2  &operator=(WrapperSDL2 const &rhs) = delete;
};

#endif	// ifndef WRAPPERSDL2_CLASS_HPP
