#include "Entity2DFactory.hpp"
#include "AssetManager.class.hpp"

#include <iostream>

namespace Entity2DFactory
{
	/* Factory method *************************************************************/
	namespace
	{
		void _getPlayer(Entity2D * entity, uint8_t mask) {
			static_cast<void>(mask);
			auto texture = AssetManager::get()->getTexture("player_f1");
			entity->texture = texture.first;
			entity->origin	= texture.second;
		}

		void _getGrass(Entity2D * entity, uint8_t mask) {
			static_cast<void>(mask);
			auto texture = AssetManager::get()->getTexture("grass_2");
			entity->texture = texture.first;
			entity->origin	= texture.second;
		}

		void _getBomb(Entity2D * entity, uint8_t mask) {
			static_cast<void>(mask);
			auto texture = AssetManager::get()->getTexture("bomb_l1");
			entity->texture = texture.first;
			entity->origin	= texture.second;
		}

		void _getFruit(Entity2D * entity, uint8_t mask) {
			static_cast<void>(mask);
			auto texture = AssetManager::get()->getTexture(FRUIT_KEY);
			entity->texture = texture.first;
			entity->origin	= texture.second;
		}

		void _getExplosion(Entity2D * entity, uint8_t mask) {
			std::pair<SDL_Texture *, SDL_Rect> texture;

			if ((mask & (ce_mask_down | ce_mask_up)) != 0 && (mask & (ce_mask_right | ce_mask_left)) != 0) {
				// SurroundedExplosion_index = 2, 18
				texture = AssetManager::get()->getTexture("explosion_nsew");
			}
			else if ((mask ^ (ce_mask_down | ce_mask_up)) == ce_mask_none) {
				// TopDownExplosion_index = 14, 14
				texture = AssetManager::get()->getTexture("explosion_ns");
			}
			else if ((mask ^ (ce_mask_right | ce_mask_left)) == ce_mask_none) {
				// RightLeftExplosion_index = 1, 18
				texture = AssetManager::get()->getTexture("explosion_ew");
			}
			else if ((mask & ce_mask_down) != 0) {
				// DownExplosion_index = 14, 15
				texture = AssetManager::get()->getTexture("explosion_s");
			}
			else if ((mask & ce_mask_up) != 0) {
				// TopExplosion_index = 14, 13
				texture = AssetManager::get()->getTexture("explosion_n");
			}
			else if ((mask & ce_mask_right) != 0) {
				// RightExplosion_index = 3, 18
				texture = AssetManager::get()->getTexture("explosion_e");
			}
			else if ((mask & ce_mask_left) != 0) {
				// LeftExplosion_index = 0, 18
				texture = AssetManager::get()->getTexture("explosion_w");
			}
			else {
				// StandAloneExplosion_index = 14, 18
				texture = AssetManager::get()->getTexture("explosion_2");
			}
			entity->texture = texture.first;
			entity->origin	= texture.second;
		}	// _getExplosion

		void _getWall(Entity2D * entity, uint8_t mask) {
			std::pair<SDL_Texture *, SDL_Rect> texture;

			if ((mask & ce_mask_down) != 0) {
				texture = AssetManager::get()->getTexture("wall_2");
			}
			else {
				texture = AssetManager::get()->getTexture("wall_1");
			}
			entity->texture = texture.first;
			entity->origin	= texture.second;
		}

		#define	SNAKE_FACTORY(function, key) \
			void function(Entity2D * entity, uint8_t mask) { \
				static_cast<void>(mask); \
				auto texture = AssetManager::get()->getTexture(key); \
				entity->texture = texture.first; \
				entity->origin	= texture.second; \
			}

		SNAKE_FACTORY(_getSnakeHeadRight, "snake_head_e")
		SNAKE_FACTORY(_getSnakeHeadLeft, "snake_head_w")
		SNAKE_FACTORY(_getSnakeHeadDown, "snake_head_s")
		SNAKE_FACTORY(_getSnakeHeadUp, "snake_head_n")
		SNAKE_FACTORY(_getSnakeTailRight, "snake_tail_e")
		SNAKE_FACTORY(_getSnakeTailLeft, "snake_tail_w")
		SNAKE_FACTORY(_getSnakeTailDown, "snake_tail_s")
		SNAKE_FACTORY(_getSnakeTailUp, "snake_tail_n")
		SNAKE_FACTORY(_getSnakeBody_RightLeft, "snake_ew")
		SNAKE_FACTORY(_getSnakeBody_UpDown, "snake_ns")
		SNAKE_FACTORY(_getSnakeBody_UpRight, "snake_ne")
		SNAKE_FACTORY(_getSnakeBody_RightDown, "snake_se")
		SNAKE_FACTORY(_getSnakeBody_DownLeft, "snake_sw")
		SNAKE_FACTORY(_getSnakeBody_LeftUp, "snake_nw")
	}// namespace

	Entity2D * entity(const t_item &item, eEntityType type, uint8_t mask) {
		auto * entity = new Entity2D(item.x, item.y);

		void(* builders[eEntityType::COUNT])(Entity2D *, uint8_t) =
		{
			_getPlayer,
			_getBomb,
			_getFruit,
			_getExplosion,
			_getWall,
			_getGrass,
			_getSnakeHeadRight,
			_getSnakeHeadLeft,
			_getSnakeHeadUp,
			_getSnakeHeadDown,
			_getSnakeTailRight,
			_getSnakeTailLeft,
			_getSnakeTailUp,
			_getSnakeTailDown,
			_getSnakeBody_RightLeft,
			_getSnakeBody_UpDown,
			_getSnakeBody_UpRight,
			_getSnakeBody_RightDown,
			_getSnakeBody_DownLeft,
			_getSnakeBody_LeftUp
		};

		builders[type](entity, mask);
		return entity;
	}
}// namespace Entity2DFactory
