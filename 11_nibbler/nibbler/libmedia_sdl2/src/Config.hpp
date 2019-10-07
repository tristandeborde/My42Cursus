#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "libmedia_interface.hpp"

constexpr SDL_Color BLACK		= {0, 0, 0, 255};
constexpr SDL_Color LIGHT_GRAY	= {100, 100, 100, 0};
constexpr SDL_Color LIGHT_BROW1 = {102, 81, 43, 255};
constexpr SDL_Color LIGHT_BROW2 = {117, 98, 64, 255};
constexpr SDL_Color BROW		= {46, 39, 25, 255};
constexpr SDL_Color WHITE		= {255, 255, 255, 255};

constexpr int MIN_BUTTON_WIDTH = 200;
constexpr int MIN_BOX_SIZE	   = 25;
constexpr int BUTTON_MARGIN	   = 5;

#ifndef BASEPATH

# define	BASEPATH "./"

#endif	// #ifndef BASEPATH

constexpr char PATH_FRUIT_BMP[]		= "libmedia_sdl2/assets/bmp/fruit.bmp";
constexpr char PATH_MENU_BMP[]		= "libmedia_sdl2/assets/bmp/border.bmp";
constexpr char PATH_BOMBERMAN_BMP[] = "libmedia_sdl2/assets/bmp/textures.bmp";
constexpr char PATH_BOMBERMAN_CSV[] = "libmedia_sdl2/assets/bmp/textures.csv";
constexpr char PATH_SNAKE_BMP[]		= "libmedia_sdl2/assets/bmp/snake_asset.bmp";
constexpr char PATH_SNAKE_CSV[]		= "libmedia_sdl2/assets/bmp/snake_asset.csv";

constexpr char PATH_OPENSB_TTF[] = "libmedia_sdl2/assets/font/OpenSans-Bold.ttf";

enum class eTextBoxType{
	Title,
	Selected,
	Basic
};

enum class eMsgType{
	Error,
	Info
};

namespace Config {
	void end(void);
	const std::map<t_game_action, SDL_Keycode> * get_map_input(void);
	const std::map<int, SDL_Keycode> * get_map_keys(void);
	const std::map<eTextBoxType, SDL_Color> * get_map_textbox(void);
}	// namespace Config


#endif	// #ifndef CONFIG_HPP
