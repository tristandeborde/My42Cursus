#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <map>

#include "libmedia_interface.hpp"
#include "libmedia_opengl.h"

constexpr SDL_Color BLACK		= {0, 0, 0, 255};
constexpr SDL_Color	LIGHT_GRAY	= {100, 100, 100, 0};
constexpr SDL_Color	LIGHT_BROW1 = {102, 81, 43, 255};
constexpr SDL_Color	LIGHT_BROW2 = {117, 98, 64, 255};
constexpr SDL_Color	BROW		= {46, 39, 25, 255};
constexpr SDL_Color	WHITE		= {255, 255, 255, 255};

#ifndef BASEPATH

# define	BASEPATH "./"

#endif	// #ifndef BASEPATH

enum class eMsgType{
	OpenGLError,
	SDLError,
	Info
};

namespace Config {
	void end(void);
	const std::map<t_game_action, SDL_Keycode> * get_map_input(void);
	const std::map<int, SDL_Keycode> * get_map_keys(void);
}	// namespace Config


#endif	// #ifndef CONFIG_HPP
