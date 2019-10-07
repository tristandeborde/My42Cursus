#ifndef WRAPPEROPENGL_CLASS_HPP
#define	WRAPPEROPENGL_CLASS_HPP

#include "libmedia_interface.hpp"

class WrapperOpenGL: public ILibMedia {
	/* Instantiation **************************************************************/
	public:
		WrapperOpenGL(void);
		~WrapperOpenGL(void) override;

	/* WrapperOpenGL Methods *********************************************************/
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
		WrapperOpenGL(WrapperOpenGL const &src) = delete;
		WrapperOpenGL  &operator=(WrapperOpenGL const &rhs) = delete;
};

#endif	// ifndef WRAPPEROPENGL_CLASS_HPP
