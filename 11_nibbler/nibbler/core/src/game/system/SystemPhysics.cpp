#include <algorithm>
#include <cmath>
#include <limits>

#include "System.hpp"

#include "Core.hpp"

#include "game/components/ComponentPlayer.class.hpp"
#include "game/components/ComponentCollision.class.hpp"
#include "game/components/ComponentMove.class.hpp"
#include "game/components/ComponentLifePoint.class.hpp"
#include "game/components/ComponentDamage.class.hpp"
#include "game/components/ComponentHasBody.class.hpp"
#include "game/components/ComponentScore.class.hpp"

#include "game/Party.class.hpp"

#include "rules/rule_spec.hpp"

#include "exceptions/CoreException.class.hpp"

#include "utils/Logger.hpp"

#include "Core.hpp"

namespace System {
	namespace Physics {
		namespace {
			void resolveBlock(const Party::t_dims &mapDim, const t_collisionData &data) {
				// Collider data
				const Vector2f collider_pos = data.collider->pos;
				const Vector2f direction	= data.collider->getComponent<ComponentMove>()->direction;
				const Vector2f sense(direction.x > 0 ? 1 : -1, direction.y > 0 ? 1 : -1);

				// Because we only deal with axis-aligned rectangles, we can use the minimal depth on one axis
				// to compute the depth on the other axis. For this, we first compute direction vector's slope.
				float slope = direction.y / direction.x;

				if (std::isnan(slope))
					slope = std::numeric_limits<float>::max();

				// We compute y_depth by multiplying x_depth with slope. (y = ax)
				Vector2f newpos_x;
				if (direction.x == 0.f)	// error handling value: longest possible vector
					newpos_x = collider_pos + Vector2f(mapDim.first, mapDim.second);
				else
					newpos_x = collider_pos - sense * Vector2f(data.x_depth, data.x_depth * slope);
				const Vector2f distance_xdepth = newpos_x - collider_pos;	// distance to original position

				// We compute x_depth by dividing y_depth with slope. (x = a/y)
				Vector2f newpos_y;
				if (direction.y == 0.f)	// error handling value: longest possible vector
					newpos_y = collider_pos + Vector2f(mapDim.first, mapDim.second);
				else
					newpos_y = collider_pos - sense * Vector2f(data.y_depth / slope, data.y_depth);
				const Vector2f distance_ydepth = newpos_y - collider_pos;	// distance to original position

				// Set the colliding rectangle's position to follow the smallest depth correction proposal:
				data.collider->pos = (distance_xdepth.norm() < distance_ydepth.norm() ?
				  fixPos(newpos_x, mapDim) : fixPos(newpos_y, mapDim));
			}	// resolveBlock

			void blockCollision(Party & party, const t_collisionData &data) {
				Vector2f new_pos = data.collider->pos;

				data.collider->pos = data.original_pos;
				if (checkCollision(data.collider, data.collidee).collided == true) {
					// the two entites were already colliding before the movement,
					// So we will allow the collider to move
					// by not resolving the collision.
					data.collider->pos = new_pos;// set back the pos
					return;
				}
				data.collider->pos = new_pos;// set back the pos

				// Rule P1007: if Collision is set, we end the game if the player trigger a block collision
				const auto & endOptLst = party.ruleSet.getVal(P1007);
				if (std::find(endOptLst.begin(), endOptLst.end(), C_End::Collision) != endOptLst.end()) {
					// check if it's the player
					if (data.collider->getComponent<ComponentPlayer>() != nullptr ||
					  data.collidee->getComponent<ComponentPlayer>() != nullptr)
					{
						// we want to trigger the specific collision func of the player (it will trigger the game over menu)
						data.collidee->getComponent<ComponentCollision>()->execute(party, data.collider);
						data.collider->getComponent<ComponentCollision>()->execute(party, data.collidee);

						// End of the game
						Core::setMode(Core::eMode::GAME_OVER);
					}
				}

				auto * collider_move_c = data.collider->getComponent<ComponentMove>();
				const auto mapDim	   = party.getDims();

				if (collider_move_c != nullptr) {
					// cancel the movement
					resolveBlock(mapDim, data);
				}
			}	// blockCollision

			void eatableCollision(Party & party, const t_collisionData &data) {
				data.collidee->getComponent<ComponentCollision>()->execute(party, data.collider);
				auto * c_score = data.collider->getComponent<ComponentScore>();
				if (c_score != nullptr)
					c_score->value += 5;
				party.destroyEntity(data.collidee);
			}

			void dealDamageCollision(Party & party, const t_collisionData &data) {
				ComponentLifePoint * tmpHP	= nullptr;
				ComponentDamage	* tmpDamage = nullptr;

				if ((tmpDamage = data.collidee->getComponent<ComponentDamage>()) == nullptr) {
					LOG(eLogType::Error,
					  "SystemPhysics: No ComponentDamage associated with 'DealDamage' collision type.");
					return;
				}
				if ((tmpHP = data.collider->getComponent<ComponentLifePoint>()) != nullptr) {
					tmpHP->subHP(static_cast<int>(tmpDamage->damage));

					if (tmpHP->getCurrentHP() == 0)
						party.destroyEntity(data.collider);
				}
			}

			void	handleCollision(Party & party, const t_collisionData &data) {
				// Unidirectional: collider is bumping into collidee
				switch (data.collidee->getComponent<ComponentCollision>()->collisionType) {
					case t_collisionType::Eatable:
						eatableCollision(party, data);
						break;
					case t_collisionType::DealDamage:
						dealDamageCollision(party, data);
						break;
					case t_collisionType::Block:
						blockCollision(party, data);
						break;
					case t_collisionType::Nothing:
						break;
				}
			}
		}	// namespace

		Vector2f fixPos(Vector2f pos, const Party::t_dims &dim) {
			// Map is circular: when you reach a limit, you go to the opposite one
			if (pos.x >= dim.first)
				pos.x -= dim.first;
			else if (pos.x < 0.f)
				pos.x += dim.first;

			if (pos.y >= dim.second)
				pos.y -= dim.second;
			else if (pos.y < 0.f)
				pos.y += dim.second;

			return pos;
		}

		t_collisionData checkCollision(Entity * collider, Entity * collidee) {
			t_collisionData data {Vector2f(), collider, collidee, 0.f, 0.f, false};

			auto * move_c = collider->getComponent<ComponentMove>();

			Vector2f pos_elem	= collider->pos;
			Vector2f size_elem	= collider->size;
			Vector2f pos_other	= collidee->pos;
			Vector2f size_other = collidee->size;

			// Get the 4 edges composing the colliding rectangle
			float left_elem	  = pos_elem.x - size_elem.x / 2;
			float right_elem  = pos_elem.x + size_elem.x / 2;
			float bottom_elem = pos_elem.y - size_elem.y / 2;
			float top_elem	  = pos_elem.y + size_elem.y / 2;

			// Get the 4 edges composing the collided rectangle
			float left_other   = pos_other.x - size_other.x / 2;
			float right_other  = pos_other.x + size_other.x / 2;
			float bottom_other = pos_other.y - size_other.y / 2;
			float top_other	   = pos_other.y + size_other.y / 2;

			// Collision check
			if ((right_elem <= left_other) || (top_elem <= bottom_other) ||
			  (right_other <= left_elem) || (top_other <= bottom_elem))
				return data;	// no Collision

			data.collided = true;

			if (move_c == nullptr)
				return data;	// no movement, so we don't need the next data

			Vector2f direction = move_c->direction;
			if (direction.x == 0.f && direction.y == 0.f)
				return data;	// no movement, so we don't need the next data

			// Get x_depth
			if (direction.x > 0.f)
				data.x_depth = right_elem - left_other;
			else
				data.x_depth = right_other - left_elem;	// swap terms otherwise difference is negative

			// Get y_depth
			if (direction.y > 0.f)
				data.y_depth = top_elem - bottom_other;
			else
				data.y_depth = top_other - bottom_elem;	// swap terms otherwise difference is negative

			return data;
		}	// checkCollision

		// quick collision check with no additionnal data
		bool			checkCollision(Entity * collider, Party::t_entityList &lst) {
			for (auto * collidee : lst) {
				if (collidee->getComponent<ComponentCollision>() == nullptr) {
					continue;
				}

				Vector2f pos_elem	= collider->pos;
				Vector2f size_elem	= collider->size;
				Vector2f pos_other	= collidee->pos;
				Vector2f size_other = collidee->size;

				// Get the 4 edges composing the colliding rectangle
				float left_elem	  = pos_elem.x - size_elem.x / 2;
				float right_elem  = pos_elem.x + size_elem.x / 2;
				float bottom_elem = pos_elem.y - size_elem.y / 2;
				float top_elem	  = pos_elem.y + size_elem.y / 2;

				// Get the 4 edges composing the collided rectangle
				float left_other   = pos_other.x - size_other.x / 2;
				float right_other  = pos_other.x + size_other.x / 2;
				float bottom_other = pos_other.y - size_other.y / 2;
				float top_other	   = pos_other.y + size_other.y / 2;

				// Collision check
				if (!((right_elem <= left_other) || (top_elem <= bottom_other) ||
				  (right_other <= left_elem) || (top_other <= bottom_elem)))
					return true;	// Collision
			}

			return false;
		}

		void update(Party & party) {
			Vector2f original_pos;
			const auto mapDim = party.getDims();

			for (auto * elem : party.entityList) {
				// Get the component move attached to the entity
				auto * move_c = elem->getComponent<ComponentMove>();
				original_pos = elem->pos;
				if (move_c != nullptr && move_c->canMove(Core::clock->now())) {
					auto * body_c = elem->getComponent<ComponentHasBody>();

					if (body_c != nullptr)
						body_c->moveBody(elem, party);
					elem->pos = fixPos(original_pos + move_c->direction, mapDim);
				}

				// Get the component collision attached to the entity
				auto * coll_c_elem = elem->getComponent<ComponentCollision>();
				if (coll_c_elem != nullptr) {
					for (auto * other : party.entityList) {
						if (other == elem)
							continue;

						auto * coll_c_other = other->getComponent<ComponentCollision>();
						if (coll_c_other != nullptr) {
							t_collisionData data = checkCollision(elem, other);
							if (data.collided) {
								data.original_pos = original_pos;
								handleCollision(party, data);
								std::swap(data.collider, data.collidee);
								handleCollision(party, data);
							}
						}
					}
				}
			}
			// delete previously destroyed entities
			party.removeDestroyedEntities();
		}	// update
	}		// namespace Physics
}			// namespace System
