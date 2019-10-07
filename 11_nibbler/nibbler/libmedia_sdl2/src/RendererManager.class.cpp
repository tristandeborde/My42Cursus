#include "RendererManager.class.hpp"
#include "Exception.class.hpp"
#include "Entity2DFactory.hpp"
#include "Config.hpp"

#include <algorithm>
#include <iostream>
#include <list>

RendererManager * RendererManager::_inst = nullptr;

RendererManager         * RendererManager::get(void) {
	if (RendererManager::_inst == nullptr) {
		RendererManager::_inst = new RendererManager();
	}
	return RendererManager::_inst;
}

SDL_Renderer * RendererManager::getRenderer(void) const{return this->_renderer;}

SDL_Window * RendererManager::getWindow(void) const{return this->_window;}

void RendererManager::begin(void) {
	/* Init SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw Exception("Error SDL_Init : ");
	}
	/* Init Window */
	this->_window = SDL_CreateWindow("Bombler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1200,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if ((this->_window) == nullptr) {
		throw Exception("Error SDL_CreateWindow : ");
	}
	/* Init Renderer */
	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_SOFTWARE);
	if ((this->_renderer) == nullptr) {
		throw Exception("Error SDL_CreateRenderer : ");
	}
}

void RendererManager::end(void) {
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);

	SDL_Quit();

	if (RendererManager::_inst != nullptr) {
		delete RendererManager::_inst;
		RendererManager::_inst = nullptr;
	}
}

void RendererManager::updateColor(const SDL_Color &color) const{
	if (SDL_SetRenderDrawColor(this->_renderer, color.r, color.g, color.b, color.a) < 0) {
		throw Exception("Error SDL_SetRenderDrawColor : ");
	}
}

void RendererManager::update(void) const{
	SDL_RenderPresent(this->_renderer);
}

void RendererManager::resetWindow(void) {
	this->updateColor({0, 0, 0, 255});
	if (SDL_RenderClear(this->_renderer) < 0) {
		throw Exception("Error SDL_RenderClear : ");
	}
	SDL_GetWindowSize(this->_window, &this->_window_width, &this->_window_height);
}

void RendererManager::resetWindow(const SDL_Color &color) {
	this->updateColor(color);
	if (SDL_RenderClear(this->_renderer) < 0) {
		throw Exception("Error SDL_RenderClear : ");
	}
	SDL_GetWindowSize(this->_window, &this->_window_width, &this->_window_height);
}

item_list_t RendererManager::bind(item_map_t map) const{
	item_list_t list;

	for (auto &item : map) {
		/* Check the surroundings of the item */
		t_ipos pos = item.first;
		std::list<t_ipos> around = {
			{pos.first,		pos.second - 1},// Up
			{pos.first,		pos.second + 1},// Down
			{pos.first - 1, pos.second	  },// Left
			{pos.first + 1, pos.second	  },// Right
		};

		uint8_t	mask = 0;
		uint8_t i	 = 0;
		for (auto & elem : around) {
			auto it = map.find(elem);
			if (it != map.end() && it->second.type == item.second.type) {
				mask |= 1 << i;
			}
			i++;
		}

		if (item.second.type == WALL) {
			list.push_front(Entity2DFactory::entity(item.second, Entity2DFactory::Wall, mask));
		}
		else {
			list.push_front(Entity2DFactory::entity(item.second, Entity2DFactory::Grass, mask));
			Entity2D * entity = nullptr;

			#define	CASE(macro, key) \
				case macro: \
					entity = Entity2DFactory::entity(item.second, key, mask); \
					break;

			switch (item.second.type) {
				CASE(BOMB, Entity2DFactory::Bomb);
				CASE(EXPLOSION, Entity2DFactory::Explosion);
				CASE(FRUIT, Entity2DFactory::Fruit);
				CASE(PLAYER, Entity2DFactory::Player);
				CASE(SNAKE_HEAD_UP, Entity2DFactory::SnakeHeadUp);
				CASE(SNAKE_HEAD_RIGHT, Entity2DFactory::SnakeHeadRight);
				CASE(SNAKE_HEAD_DOWN, Entity2DFactory::SnakeHeadDown);
				CASE(SNAKE_HEAD_LEFT, Entity2DFactory::SnakeHeadLeft);
				CASE(SNAKE_TAIL_UP, Entity2DFactory::SnakeTailUp);
				CASE(SNAKE_TAIL_RIGHT, Entity2DFactory::SnakeTailRight);
				CASE(SNAKE_TAIL_DOWN, Entity2DFactory::SnakeTailDown);
				CASE(SNAKE_TAIL_LEFT, Entity2DFactory::SnakeTailLeft);
				CASE(SNAKE_UP_DOWN, Entity2DFactory::SnakeBody_UpDown);
				CASE(SNAKE_RIGHT_LEFT, Entity2DFactory::SnakeBody_RightLeft);
				CASE(SNAKE_UP_RIGHT, Entity2DFactory::SnakeBody_UpRight);
				CASE(SNAKE_RIGHT_DOWN, Entity2DFactory::SnakeBody_RightDown);
				CASE(SNAKE_DOWN_LEFT, Entity2DFactory::SnakeBody_DownLeft);
				CASE(SNAKE_LEFT_UP, Entity2DFactory::SnakeBody_LeftUp);
				case WALL:
				case EMPTY:
					break;
			}
			if (entity != nullptr)
				list.push_back(entity);
		}
	}
	return list;
}	// RendererManager::bind

void RendererManager::draw(item_list_t list, size_t w, size_t h) const{
	auto del = [](Entity2D * entity) {
		  delete entity;
		  return true;
	  };
	SDL_Rect base = getBoxShape(w, h);

	for (auto &elem : list) {
		SDL_Rect rect = base;

		if (elem->texture == nullptr)
			continue;

		rect.x += static_cast<int>(elem->x * rect.w);
		rect.y += static_cast<int>(elem->y * rect.w);

		if (SDL_RenderCopy(RendererManager::get()->getRenderer(), elem->texture, &(elem->origin), &rect) < 0) {
			if (!list.empty()) {
				std::for_each(list.begin(), list.end(), del);
				list.clear();
			}
			throw Exception("Error SDL_RenderCopy : ");
		}
	}
	std::for_each(list.begin(), list.end(), del);
	list.clear();
}

SDL_Rect RendererManager::getBoxShape(size_t w, size_t h) const{
	SDL_Rect rect = {0, 0, 0, 0};
	auto width(static_cast<int>(w)), height(static_cast<int>(h));

	rect.h = rect.w = (this->_window_width / width < this->_window_height / height) ?
	  this->_window_width / width : this->_window_height / height;

	if (rect.h < MIN_BOX_SIZE) {
		rect.h = rect.w = MIN_BOX_SIZE;
	}
	rect.x = (this->_window_width - width * rect.h) / 2;
	rect.y = (this->_window_height - height * rect.w) / 2;
	return rect;
}

SDL_Rect RendererManager::getButtonShape(size_t nb_button) const{
	SDL_Rect rect = {0, 0, 0, 0};
	auto nb(static_cast<int>(nb_button));

	if (this->_window_width > MIN_BUTTON_WIDTH * 3) {
		rect.w = this->_window_width / 3;
	}
	else {
		rect.w = MIN_BUTTON_WIDTH;
	}
	rect.h = rect.w / 3;
	rect.x = (this->_window_width - rect.w) / 2;
	rect.y = (this->_window_height - rect.h * nb) / 2;
	return rect;
}
