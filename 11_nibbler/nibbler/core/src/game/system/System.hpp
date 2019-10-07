#ifndef SYSTEM_HPP
#define	SYSTEM_HPP

#include "Vector2.class.hpp"

#include "game/Party.class.hpp"

namespace System {
	/*
	 * Systems are used to update all the data used during the game
	 * So far, we have 4 systems:
	 * - Input		: get the user input while playing
	 * - Physics	: handle movement and collisions between entities
	 * - Render		: compute the frame to be rendered
	 * - Timer		: deal with timer-based events
	 */

	namespace Input {
		void	update(Party & party);
	}	// namespace Input

	namespace Physics {
		struct t_collisionData{
			Vector2f original_pos;	// for collider
			Entity * collider;
			Entity * collidee;
			float	 x_depth;
			float	 y_depth;
			bool	 collided;
		};

		void	update(Party & party);

		// check if a there is a collision between 2 entities
		t_collisionData	checkCollision(Entity * collider, Entity * collidee);
		// check if there is a collision between an entity and a list of entity
		bool			checkCollision(Entity * collider, Party::t_entityList &lst);

		// return a new position that respect the circular attribute of the map
		Vector2f fixPos(Vector2f pos, const Party::t_dims &dim);
	}	// namespace Physics

	namespace Render {
		void	update(Party & party);
	}	// namespace Render

	namespace Timer {
		void	update(Party & party);
	}	// namespace Timer
}		// namespace System

#endif	// SYSTEM_HPP
