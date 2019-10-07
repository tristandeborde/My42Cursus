#ifndef ENTITY2DFACTORY_HPP
#define	ENTITY2DFACTORY_HPP

#include "Entity2D.struct.hpp"
#include "libmedia_sdl2.h"

constexpr uint32_t ce_mask_none	 = 0x0;
constexpr uint32_t ce_mask_up	 = 0x1;
constexpr uint32_t ce_mask_down	 = 0x2;
constexpr uint32_t ce_mask_right = 0x4;
constexpr uint32_t ce_mask_left	 = 0x8;

namespace Entity2DFactory
{
	enum eEntityType{
		Player = 0,
		Bomb,
		Fruit,
		Explosion,
		Wall,
		Grass,
		SnakeHeadRight,
		SnakeHeadLeft,
		SnakeHeadUp,
		SnakeHeadDown,
		SnakeTailRight,
		SnakeTailLeft,
		SnakeTailUp,
		SnakeTailDown,
		SnakeBody_RightLeft,
		SnakeBody_UpDown,
		SnakeBody_UpRight,
		SnakeBody_RightDown,
		SnakeBody_DownLeft,
		SnakeBody_LeftUp,
		COUNT
	};

	Entity2D * entity(const t_item &item, eEntityType type, uint8_t mask);
}// namespace Entity2DFactory

#endif	// ENTITY2DFACTORY_HPP
