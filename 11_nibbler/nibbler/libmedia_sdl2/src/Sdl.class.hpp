#ifndef SDL_CLASS_HPP
#define	SDL_CLASS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "libmedia_sdl2.h"

#include <deque>
#include <string>

#include "RendererManager.class.hpp"
#include "Config.hpp"

/* Typedefs *******************************************************************/
using t_map_textures = struct s_map_textures{
	t_case		  c;
	SDL_Texture	* texture;
};

class Sdl
{
	private:
		static Sdl * _inst;

	/* Instantiation **************************************************************/
	public:
		static Sdl * get(void);

	/* Methods ********************************************************************/
	public:
		t_input     input(void);
		int         drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score);
		int         drawmenu(t_menu menu);
		int         begin(void);
		void        end(void);
		const char * getlog(void);

	private:
		Sdl(void) = default;

		int         draw_object(float x, float y, t_case c, SDL_Rect rect);
		int			draw_textbox(const SDL_Rect &rect, const char * msg, eTextBoxType type);
		item_map_t build_map(size_t width, size_t height, t_item * items, size_t nb_items);

		t_input		input_game(t_input input, SDL_Event e) const;
		t_input		input_menu(t_input input, SDL_Event e);

		void        log(const std::string & msg, eMsgType err);
		void        log(const std::string & msg);

	/* Attributes *****************************************************************/
	private:
		std::deque<std::string>	_logs {};
		bool _ingame {true};
		size_t _selectedButton {0};
		size_t _buttonNumber {0};

	/* Coplien methods ************************************************************/
	public:
		~Sdl(void)		= default;
		Sdl(const Sdl&) = delete;
		Sdl& operator=(const Sdl&) = delete;
};

#endif	// #ifndef SDL_CLASS_HPP
