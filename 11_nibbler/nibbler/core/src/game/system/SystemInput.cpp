#include <string>
#include <stdexcept>

#include "System.hpp"

#include "Vector2.class.hpp"
#include "Core.hpp"

#include "utils/GraphicsLoader.hpp"
#include "utils/Logger.hpp"

#include "game/components/ComponentPlayer.class.hpp"
#include "game/components/ComponentMove.class.hpp"
#include "game/components/ComponentCollision.class.hpp"
#include "game/components/ComponentHasBody.class.hpp"

#include "game/Party.class.hpp"
#include "game/EntityFactory.hpp"

namespace System {
	namespace Input {
		namespace {
			void dropBomb(Party & party, const Vector2f & pos) {
				// check if their is no bomb at this position
				auto * newBomb = EntityFactory::entity(EntityFactory::eEntityType::Bomb, pos);

				for (auto * elem : party.entityList) {
					auto * coll_c = elem->getComponent<ComponentCollision>();
					if (coll_c == nullptr || coll_c->collisionType != t_collisionType::Block)
						continue;
					Physics::t_collisionData data = System::Physics::checkCollision(newBomb, elem);
					if (data.collided) {
						// Their is already something ! can't drop the bomb
						delete newBomb;
						return;
					}
				}

				party.addEntity(newBomb);
			}

			void chooseDirection(Party & party, const Entity * entity, const t_game_action &input) {
				Vector2f new_dir;

				switch (input) {
					case (t_game_action::GAME_DROP_BOMB):
						if (party.ruleSet.getVal(P1012))// can we drop a bomb
							dropBomb(party, entity->pos);
						return;

					case (t_game_action::GAME_UP):
						new_dir = Vector2f(0.f, -1.f);
						break;
					case (t_game_action::GAME_DOWN):
						new_dir = Vector2f(0.f, 1.f);
						break;
					case (t_game_action::GAME_LEFT):
						new_dir = Vector2f(-1.f, 0.f);
						break;
					case (t_game_action::GAME_RIGHT):
						new_dir = Vector2f(1.f, 0.f);
						break;
				}

				auto * move_c = entity->getComponent<ComponentMove>();
				if (!party.ruleSet.getVal(P1010)) {	// has body
					move_c->direction = new_dir;
				}
				else {
					auto * body_c = entity->getComponent<ComponentHasBody>();
					if (body_c == nullptr) {
						LOG(eLogType::Error, "sInput: rule P1010 is activated, but player has no ComponentHasBody");
						return;
					}
					if (body_c->entityList.empty() ||
					  (body_c->entityList.front()->pos - entity->pos) != new_dir)	// is it not a 180 degree rotation
					{
						move_c->direction = new_dir;
					}
				}
			}	// chooseDirection
		}		// namespace

		void update(Party & party) {
			const t_input input = GraphicsLoader::libmedia_input();

			if (input.type == EXIT) {
				Core::setMode(Core::eMode::EXIT);
			}
			else if (input.type == ECHAP) {
				Core::setMode(Core::eMode::MENU);
			}
			else if (input.type == GAME || input.type == NO_INPUT) {
				for (const auto &elem : party.entityList) {
					// Get the entity with a component player attached
					auto * tmp = elem->getComponent<ComponentPlayer>();

					if (tmp == nullptr)
						continue;

					// Get the component move attached to the entity
					auto * move_c = elem->getComponent<ComponentMove>();
					if (move_c == nullptr) {
						// Cannot have a player without a component move
						throw std::runtime_error(
								"missing 'ComponentMove' from Entity '"
								+ std::to_string(elem->id)
								+ "' with 'ComponentPlayer' attached");
					}
					if (input.type == NO_INPUT && !party.ruleSet.getVal(M2001))	// can we stop moving
						move_c->direction = Vector2f(0.f, 0.f);
					else if (input.type == GAME)
						chooseDirection(party, elem, input.u_input_raw.game);
				}
			}
		}	// update
	}		// namespace Input
}			// namespace System
