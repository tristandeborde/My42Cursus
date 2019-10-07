#include "Config.hpp"

namespace Config
{
	namespace
	{
		std::map<eTextBoxType, SDL_Color> * map_textbox = nullptr;
		std::map<int, SDL_Keycode> * map_keys = nullptr;
		std::map<t_game_action, SDL_Keycode> * map_input = nullptr;
	}	// namespace

	const std::map<t_game_action, SDL_Keycode> * get_map_input(void) {
		if (map_input == nullptr) {
			map_input = new std::map<t_game_action, SDL_Keycode>();
			map_input->insert({GAME_LEFT, SDLK_LEFT});
			map_input->insert({GAME_RIGHT, SDLK_RIGHT});
			map_input->insert({GAME_DOWN, SDLK_DOWN});
			map_input->insert({GAME_UP, SDLK_UP});
			map_input->insert({GAME_DROP_BOMB, SDLK_SPACE});
		}
		return map_input;
	}

	const std::map<int, SDL_Keycode> * get_map_keys(void) {
		if (map_keys == nullptr) {
			map_keys = new std::map<int, SDL_Keycode> ();
			map_keys->insert({1, SDLK_1});
			map_keys->insert({2, SDLK_2});
			map_keys->insert({3, SDLK_3});
			map_keys->insert({4, SDLK_4});
			map_keys->insert({5, SDLK_5});
			map_keys->insert({6, SDLK_6});
			map_keys->insert({7, SDLK_7});
			map_keys->insert({8, SDLK_8});
			map_keys->insert({9, SDLK_9});
		}
		return map_keys;
	}

	const std::map<eTextBoxType, SDL_Color> * get_map_textbox(void) {
		if (map_textbox == nullptr) {
			map_textbox = new std::map<eTextBoxType, SDL_Color>();
			map_textbox->insert({eTextBoxType::Title, BROW});
			map_textbox->insert({eTextBoxType::Selected, LIGHT_BROW2});
			map_textbox->insert({eTextBoxType::Basic, LIGHT_BROW1});
		}
		return map_textbox;
	}

	void end(void) {
		delete map_textbox;
		map_textbox = nullptr;
		delete map_keys;
		map_keys = nullptr;
		delete map_input;
		map_input = nullptr;
	}
}	// namespace Config
