#include <random>
#include <algorithm>

#include "EntityFactory.hpp"
#include "Party.class.hpp"

#include "game/components/ComponentMove.class.hpp"
#include "game/components/ComponentPlayer.class.hpp"
#include "game/components/ComponentCollision.class.hpp"
#include "game/components/ComponentDamage.class.hpp"
#include "game/components/ComponentLifePoint.class.hpp"
#include "game/components/ComponentRender.class.hpp"
#include "game/components/ComponentTimerEvent.class.hpp"
#include "game/components/ComponentOnDeathEvent.class.hpp"
#include "game/components/ComponentHasBody.class.hpp"
#include "game/components/ComponentScore.class.hpp"

#include "game/system/System.hpp"

#include "rules/rule_spec.hpp"

#include "utils/Logger.hpp"


namespace EntityFactory
{
	/* Factory method *************************************************************/
	namespace
	{
		t_entity_id g_id_count	 = 0;
		const RuleSet * _ruleset = nullptr;

		void _createPlayer(Entity * entity) {
			if (_ruleset->getVal(P1011)) {	// P1011: increase speed over time
				auto timerEvent = [](Party & party, Entity * _entity) {
					  static_cast<void>(party);
					  float speed = _entity->getComponent<ComponentMove>()->speed;

					  speed *= 1.3f;		// acceleration factor
					  if (speed >= 15.f) {	// speed limits
						  _entity->getComponent<ComponentMove>()->speed = 15.f;
						  return;
					  }

					  _entity->getComponent<ComponentMove>()->speed = speed;
					  _entity->getComponent<ComponentTimerEvent>()->startTimer();	// reset the timer
				  };

				entity->addComponent(new ComponentTimerEvent(std::chrono::seconds(10), std::move(timerEvent)));
			}

			if (_ruleset->getVal(P1010)) {	// P1010: Player has a body
				entity->addComponent(new ComponentHasBody());

				auto onDeathEvent = [](Party & party, Entity * _entity) {
					  if (!_entity->getComponent<ComponentHasBody>()->entityList.empty()) {
						  party.popEntity(_entity->getComponent<ComponentHasBody>()->entityList.front());	// it will delete all the body
					  }
				  };
				entity->addComponent(new ComponentOnDeathEvent(std::move(onDeathEvent)));
			}

			auto onCollisionEvent = [](Party & party, Entity * _entity) {
				  static_cast<void>(_entity);

					// timer before opening the Game Over menu
				  party.addEntity(EntityFactory::entity(eEntityType::MenuTimer, Vector2f(-1.f, -1.f)));
			  };

			entity->addComponent(new ComponentPlayer());
			entity->addComponent(new ComponentCollision(t_collisionType::Nothing, std::move(onCollisionEvent)));
			entity->addComponent(new ComponentLifePoint(1));
			entity->addComponent(new ComponentMove(Vector2f(1.f, 0.f), 2.f));	// default direction for Automove Rule. We shall find a way to set it in another way
			entity->addComponent(new ComponentRender(PLAYER));
			entity->addComponent(new ComponentScore());
		}	// _createPlayer

		void _createBomb(Entity * entity) {
			// timerEvent: Destroy the entity
			auto timerEvent = [](Party & party, Entity * _entity) {
				  party.destroyEntity(_entity);
			  };

			// OnDeathEvent: Generate explosion entities
			auto onDeathEvent = [](Party & party, Entity * _entity) {
				  Vector2f entityPos = _entity->pos;

					// we must add 5 explosion entities, on the bomb itself and on each side of the bomb
				  party.addEntity(EntityFactory::entity(EntityFactory::eEntityType::Explosion, entityPos));
				  entityPos = System::Physics::fixPos(entityPos + Vector2f(1.f, 0.f), party.getDims());
				  party.addEntity(EntityFactory::entity(EntityFactory::eEntityType::Explosion, entityPos));
				  entityPos = System::Physics::fixPos(entityPos - Vector2f(2.f, 0.f), party.getDims());
				  party.addEntity(EntityFactory::entity(EntityFactory::eEntityType::Explosion, entityPos));
				  entityPos = System::Physics::fixPos(entityPos + Vector2f(1.f, 1.f), party.getDims());
				  party.addEntity(EntityFactory::entity(EntityFactory::eEntityType::Explosion, entityPos));
				  entityPos = System::Physics::fixPos(entityPos - Vector2f(0.f, 2.f), party.getDims());
				  party.addEntity(EntityFactory::entity(EntityFactory::eEntityType::Explosion, entityPos));
			  };

			entity->addComponent(new ComponentCollision(t_collisionType::Block));
			entity->addComponent(new ComponentLifePoint(1));
			entity->addComponent(new ComponentOnDeathEvent(std::move(onDeathEvent)));
			entity->addComponent(new ComponentTimerEvent(std::chrono::seconds(3), std::move(timerEvent)));
			entity->addComponent(new ComponentRender(BOMB));
		}	// _createBomb

		void _createWall(Entity * entity) {
			entity->addComponent(new ComponentCollision(t_collisionType::Block));
			entity->addComponent(new ComponentRender(WALL));
		}

		void _createDestructibleWall(Entity * entity) {
			entity->addComponent(new ComponentCollision(t_collisionType::Block));
			entity->addComponent(new ComponentLifePoint(1));
			// todo(julienhache): destructible walls should have a different t_case value
			entity->addComponent(new ComponentRender(WALL));
		}

		void _createFruit(Entity * entity) {
			ComponentCollision::t_collision_event onEatEvent = [](Party & party, Entity * _entity) {
				  if (party.ruleSet.getVal(P1010) && _entity->getComponent<ComponentPlayer>() != nullptr) {
					  _entity->getComponent<ComponentHasBody>()->addBody();	// fruit make the body to grow
				  }
			  };

			entity->addComponent(new ComponentCollision(t_collisionType::Eatable, std::move(onEatEvent)));
			{// respawnable fruit
				const auto & inGameObjLst = _ruleset->getVal(P1022);// P1022: in game obj

				if (std::find(inGameObjLst.begin(), inGameObjLst.end(), C_Object::Fruit) != inGameObjLst.end() &&
				  _ruleset->getVal(P1024) == C_Freq::OneByOne)	// P1024: spawn frequency of P1022
				{
					auto onDeathEvent = [](Party & party, Entity * _entity) {
						  static_cast<void>(_entity);
						  const auto map_dim = party.getDims();
							// Random number generator
						  std::uniform_int_distribution<size_t>	randX(1, map_dim.first - 2);
						  std::uniform_int_distribution<size_t>	randY(1, map_dim.second - 2);
						  static auto eng = std::default_random_engine(static_cast<unsigned int>(std::time(nullptr)));	// static because it will be reset at destruction
						  Vector2f obj_pos(randX(eng), randY(eng));

						  Entity * new_obj = EntityFactory::entity(eEntityType::Fruit, obj_pos);

							// since the pos generation can fail (collision), we have a count for retry
						  int _count = 50;
						  while (--_count > 0) {// check collision before adding the entity
							  new_obj->pos = obj_pos;

							  if (!System::Physics::checkCollision(new_obj, party.entityList))	// if there is no collision
								  break;
							  obj_pos = Vector2f(randX(eng), randY(eng));
						  }

						  if (_count > 0) {
							  party.addEntity(new_obj);
						  }
						  else {// we failed 50 times to create the object on an empty case
							  LOG(eLogType::Warning, "P1022: Can't respawn the fruit");
							  delete new_obj;
						  }
					  };
					entity->addComponent(new ComponentOnDeathEvent(std::move(onDeathEvent)));
				}
			}

			entity->addComponent(new ComponentRender(FRUIT));
		}	// _createFruit

		void _createExplosion(Entity * entity) {
			// timerEvent: Destroy the entity
			auto timerEvent = [](Party & party, Entity * _entity) {
				  party.destroyEntity(_entity);
			  };

			entity->addComponent(new ComponentCollision(t_collisionType::DealDamage));
			entity->addComponent(new ComponentDamage(1));
			entity->addComponent(new ComponentRender(EXPLOSION));
			entity->addComponent(new ComponentTimerEvent(std::chrono::milliseconds(1500), std::move(timerEvent)));
		}

		void _createSpawner(Entity * entity) {
			// timerEvent: create an object from the P1022 rule (in-game spawnable objects list)
			auto timerEvent = [](Party & party, Entity * _entity) {
				  auto & obj_list = party.ruleSet.getVal(P1022);

				  if (obj_list.empty()) {
					  LOG(eLogType::Error, "P1022: Spawner have been created with no object in the list.");
					  party.destroyEntity(_entity);
					  return;
				  }
				  const auto map_dim = party.getDims();
					// Random number generator
				  std::uniform_int_distribution<size_t>	randX(1, map_dim.first - 2);
				  std::uniform_int_distribution<size_t>	randY(1, map_dim.second - 2);
				  std::uniform_int_distribution<size_t>	randObj(0, obj_list.size() - 1);
					// static engine because otherwise it would be reset at destruction
				  static auto eng = std::default_random_engine(static_cast<unsigned int>(std::time(nullptr)));
				  Vector2f obj_pos(randX(eng), randY(eng));

				  Entity * new_obj = EntityFactory::entity(C_ObjectToEntityType(obj_list[randObj(eng)]), obj_pos);

					// since the pos generation can fail (collision), we have a count for retry
				  int _count = 10;
				  while (--_count > 0) {// check collision before adding the entity
					  new_obj->pos = obj_pos;
					  if (!System::Physics::checkCollision(new_obj, party.entityList))	// if there is no collision
						  break;
					  obj_pos = Vector2f(randX(eng), randY(eng));
				  }
				  if (_count > 0) {
					  party.addEntity(new_obj);
				  }
				  else {// we failed 10 times to create the object on an empty case
					  LOG(eLogType::Warning, "P1022: Can't create the object");
					  delete new_obj;
				  }

				  _entity->getComponent<ComponentTimerEvent>()->startTimer();	// reset the timer
			  };

			// Spawn frequency
			int ms_treshold;

			switch (_ruleset->getVal(P1024)) {
				case (C_Freq::VeryRare):
					ms_treshold = 15000;
					break;
				case (C_Freq::Rare):
					ms_treshold = 6000;
					break;
				case (C_Freq::OneByOne):// not handled here
				case (C_Freq::Normal):
					ms_treshold = 3000;
					break;
				case (C_Freq::Frequent):
					ms_treshold = 1500;
					break;
				case (C_Freq::VeryFrequent):
					ms_treshold = 500;
					break;
			}

			entity->addComponent(new ComponentTimerEvent(std::chrono::milliseconds(ms_treshold),
					std::move(timerEvent)));
		}	// _createSpawner

		void _createMenuTimer(Entity * entity) {
			// timerEvent: set the Core mode to MENU after 2 seconds
			auto timerEvent = [](Party & party, Entity * _entity) {
				  static_cast<void>(party);
				  static_cast<void>(_entity);
				  Core::setMode(Core::eMode::MENU);
			  };

			entity->addComponent(new ComponentTimerEvent(std::chrono::milliseconds(2000), std::move(timerEvent)));
		}

		void _createBody(Entity * entity) {
			entity->addComponent(new ComponentLifePoint(1));
			entity->addComponent(new ComponentCollision(t_collisionType::Block));
			entity->addComponent(new ComponentRender(PLAYER));	// will be computed later
		}
	}// namespace

	std::ostream &operator<<(std::ostream &os, eEntityType type) {
		#define	C(x) \
			case x: \
				os << # x; break;
		switch (type) {
			C(Player)
			C(Bomb)
			C(Wall)
			C(DestructibleWall)
			C(Fruit)
			C(Explosion)
			C(Spawner)
			C(MenuTimer)
			C(Body)
			case COUNT:
				os << "This type doesn't exist";
				break;
		}
		#undef C
		return os;
	}

	Entity * entity(eEntityType type, const Vector2f &pos, const Vector2f &size) {
		void(* builders[eEntityType::COUNT])(Entity *) =
		{
			_createPlayer,
			_createBomb,
			_createWall,
			_createDestructibleWall,
			_createFruit,
			_createExplosion,
			_createSpawner,
			_createMenuTimer,
			_createBody
		};

		if (_ruleset == nullptr) {
			LOG(eLogType::Error, "EntityFactory: No ruleset has been given. You shall call EntityFactory::setRules().");
			return nullptr;
		}

		Entity * entity;
		entity = new Entity(g_id_count, pos, size);

		builders[type](entity);
		++g_id_count;
		LOG(eLogType::Info, "entity created (", type, ") at", pos);
		return entity;
	}

	void linkElemToBody(Entity * elem, ComponentHasBody * body) {
		// We will add a OnDeathComponent, to link each body with the next one.
		auto onDeathEvent = [ = ](Party & party, Entity * entity) {
			  auto it = std::find(body->entityList.begin(), body->entityList.end(), entity);

			  if (it == body->entityList.end()) {
				  LOG(eLogType::Error, "EntityFactory: body entity with no owner. ComponentHasBody == ", body,
					"&& body entity == ", entity);
			  }
			  else {
				  auto next_it = body->entityList.erase(it);
				  if (next_it != body->entityList.end())
					  party.popEntity(*next_it);
			  }
		  };

		elem->addComponent(new ComponentOnDeathEvent(std::move(onDeathEvent)));
	}

	void setRules(const RuleSet * ruleset) {
		_ruleset = ruleset;
	}

	EntityFactory::eEntityType		C_ObjectToEntityType(const C_Object & obj) {
		switch (obj) {
			case C_Object::Bomb:
				return (EntityFactory::eEntityType::Bomb);

			case C_Object::DestructibleWall:
				return (EntityFactory::eEntityType::DestructibleWall);

			case C_Object::Fruit:
				return (EntityFactory::eEntityType::Fruit);
		}
	}
}// namespace EntityFactory
