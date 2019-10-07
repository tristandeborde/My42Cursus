#include "Sdl.class.hpp"
#include "Exception.class.hpp"
#include "AssetManager.class.hpp"
#include <iostream>

Sdl * Sdl::_inst = nullptr;

Sdl         * Sdl::get(void) {
	if (Sdl::_inst == nullptr) {
		Sdl::_inst = new Sdl();
	}
	return Sdl::_inst;
}

int Sdl::begin(void) {
	try
	{
		RendererManager::get()->begin();
		AssetManager::get()->begin();
		RendererManager::get()->resetWindow();
	}
	catch (const Exception& e)
	{
		this->log(e.what(), eMsgType::Error);
		return -1;
	}
	this->log("Sdl::begin");
	return 0;
}

void Sdl::end(void) {
	AssetManager::get()->end();
	RendererManager::get()->end();
	Config::end();

	this->_logs.clear();

	if (Sdl::_inst != nullptr) {
		delete Sdl::_inst;
		Sdl::_inst = nullptr;
	}
}

t_input Sdl::input_game(t_input input, SDL_Event e) const{
	for (auto const &elem : *Config::get_map_input()) {
		if (elem.second == e.key.keysym.sym) {
			input.type = GAME;
			input.u_input_raw.game = elem.first;
		}
	}
	return input;
}

t_input Sdl::input_menu(t_input input, SDL_Event e) {
	if (e.key.keysym.sym == SDLK_DOWN && this->_selectedButton < this->_buttonNumber - 1) {
		++this->_selectedButton;
	}
	else if (e.key.keysym.sym == SDLK_UP && this->_selectedButton > 0) {
		--this->_selectedButton;
	}
	else if (e.key.keysym.sym == SDLK_RETURN) {
		input.type = MENU;
		input.u_input_raw.menu = {MENU_CLICK, this->_selectedButton};
		// reset cursor position
		this->_selectedButton = 0;
	}
	return input;
}

t_input Sdl::input(void) {
	t_input input;
	SDL_Event e;

	bzero(&input, sizeof(input));
	input.type = NO_INPUT;
	SDL_PollEvent(&e);
	if (e.type == SDL_KEYDOWN) {
		for (auto const &elem : *Config::get_map_keys()) {
			if (elem.second == e.key.keysym.sym) {
				input.type = RCHANGE;
				input.u_input_raw.rchange = elem.first;
				return input;
			}
		}
		if (this->_ingame == true)
			input = this->input_game(input, e);
		else
			input = this->input_menu(input, e);
		if (SDLK_ESCAPE == e.key.keysym.sym) {
			input.type = ECHAP;
		}
	}
	if (e.type == SDL_QUIT || (e.type == SDL_WINDOWEVENT &&
	  e.window.event == SDL_WINDOWEVENT_CLOSE))
	{
		input.type = EXIT;
	}
	return input;
}

item_map_t Sdl::build_map(size_t width, size_t height, t_item * items, size_t nb_items) {
	item_map_t map;

	for (size_t i = 0; i < nb_items; ++i) {
		if (items[i].x >= 0 && items[i].y >= 0 && items[i].x <= width && items[i].y <= height) {
			map.insert({{static_cast<int32_t>(items[i].x), static_cast<int32_t>(items[i].y)}, items[i]});
		}
	}
	for (size_t x = 0; x < width; ++x) {
		for (size_t y = 0; y < height; ++y) {
			auto it = map.find(t_ipos(x, y));
			if (it == map.end()) {
				map.insert({{static_cast<int32_t>(x), static_cast<int32_t>(y)},
					  {EMPTY, static_cast<float>(x), static_cast<float>(y)}});
			}
		}
	}
	return map;
}

int Sdl::drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score) {
	if (this->_ingame == false) {
		this->_ingame = true;
		this->log("First drawgame.");
	}
	RendererManager::get()->resetWindow(LIGHT_GRAY);
	item_map_t map	 = build_map(width, height, items, nb_items);
	item_list_t list = RendererManager::get()->bind(map);
	RendererManager::get()->draw(list, width, height);
	this->draw_textbox({0, 0, 100, 100}, std::to_string(score).c_str(), eTextBoxType::Basic);
	RendererManager::get()->update();
	return 0;
}

int	Sdl::draw_textbox(const SDL_Rect &rect, const char * msg, eTextBoxType type) {
	SDL_Rect rectext = rect;

	for (auto const &elem : *Config::get_map_textbox()) {
		if (elem.first == type) {
			RendererManager::get()->updateColor(elem.second);
			break;
		}
	}

	if (type != eTextBoxType::Title) {
		rectext.x += BUTTON_MARGIN;
		rectext.y += BUTTON_MARGIN;
		rectext.w -= BUTTON_MARGIN * 2;
		rectext.h -= BUTTON_MARGIN * 2;
	}

	if (SDL_RenderFillRect(RendererManager::get()->getRenderer(), &rectext) < 0) {
		this->log("Error SDL_RenderFillRect : ", eMsgType::Error);
		return -1;
	}

	if (type != eTextBoxType::Title &&
	  SDL_RenderCopy(RendererManager::get()->getRenderer(), AssetManager::get()->getTexture(MENU_KEY).first,
	  nullptr,
	  &rectext) < 0)
	{
		this->log("Error SDL_RenderCopy : ", eMsgType::Error);
		return -1;
	}

	SDL_Surface * surface = nullptr;

	if ((surface = TTF_RenderText_Blended(AssetManager::get()->getFont(FONT_KEY), msg, WHITE)) == nullptr) {
		this->log("Error TTF_RenderText_Blended : ", eMsgType::Error);
		return -1;
	}
	SDL_Texture * texture = nullptr;
	if ((texture = SDL_CreateTextureFromSurface(RendererManager::get()->getRenderer(), surface)) == nullptr) {
		this->log("Error SDL_CreateTextureFromSurface : ", eMsgType::Error);
		SDL_FreeSurface(surface);
		return -1;
	}

	if (type == eTextBoxType::Title) {
		rectext.x += rect.w / 12;
		rectext.y += rect.h / 20;
		rectext.w  = rect.w - (rect.w / 12 * 2);
		rectext.h  = rect.h - (rect.h / 20 * 2);
	}
	else {
		rectext.h = (rect.h * 6) / 10;
		rectext.y = rect.y + (rect.h * 2) / 10;
		rectext.w = (surface->w * rectext.h) / surface->h;
		rectext.x = rect.x + (rect.w - rectext.w) / 2;
	}

	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(RendererManager::get()->getRenderer(), texture, nullptr, &rectext) < 0) {
		this->log("Error SDL_RenderCopy : ", eMsgType::Error);
		SDL_DestroyTexture(texture);
		return -1;
	}
	SDL_DestroyTexture(texture);
	return 0;
}	// Sdl::draw_textbox

int Sdl::drawmenu(t_menu menu) {
	if (this->_ingame == true) {
		this->_ingame = false;
		this->log("First drawmenu.");
	}

	this->_buttonNumber = menu.nb_buttons;
	SDL_Rect rect = RendererManager::get()->getButtonShape(menu.nb_buttons);

	RendererManager::get()->resetWindow(LIGHT_GRAY);
	this->draw_textbox(rect, menu.title, eTextBoxType::Title);
	for (size_t i = 0; i < menu.nb_buttons; i++) {
		rect.y += rect.h;
		if (this->_selectedButton == i)
			this->draw_textbox(rect, menu.li_buttons[i].title, eTextBoxType::Selected);
		else
			this->draw_textbox(rect, menu.li_buttons[i].title, eTextBoxType::Basic);
	}
	RendererManager::get()->update();
	return 0;
}

const char	* Sdl::getlog(void) {
	const char * msg;

	if (_logs.empty() == false) {
		msg = _logs.front().c_str();
		_logs.pop_front();
	}
	else {
		return nullptr;
	}
	return msg;
}

void Sdl::log(const std::string & msg, eMsgType err) {
	std::string	log = msg;

	if (eMsgType::Error == err) {
		log.append(SDL_GetError());
	}
	_logs.push_back(log);
}

void Sdl::log(const std::string & msg) {
	_logs.push_back(msg);
}
