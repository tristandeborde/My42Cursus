#ifndef WRAPPERNCURSES_CLASS_HPP
#define	WRAPPERNCURSES_CLASS_HPP

#include "libmedia_interface.hpp"
#include "Renderer.class.hpp"

class WrapperNcurses: public ILibMedia {
	/* Instantiation **************************************************************/
	public:
		WrapperNcurses(void);
		~WrapperNcurses(void) override;

	/* WrapperNcurses Methods *********************************************************/
	public:
		void         libmedia_begin(void) override;
		void         libmedia_end(void) override;
		void         libmedia_drawgame(size_t width, size_t height, t_item * items, size_t nb_items,
			uint32_t score) override;
		void         libmedia_drawmenu(t_menu menu) override;
		t_input      libmedia_input(void) override;
		const char * libmedia_getlog(void) override;

	private:
		Renderer * renderer;

	/* Coplien Methods ************************************************************/
	public:
		WrapperNcurses(WrapperNcurses const &src) = delete;
		WrapperNcurses  &operator=(WrapperNcurses const &rhs) = delete;
};

#endif	// ifndef WRAPPERNCURSES_CLASS_HPP
