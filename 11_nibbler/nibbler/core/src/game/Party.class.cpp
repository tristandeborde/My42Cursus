#include <algorithm>

#include "Party.class.hpp"
#include "EntityFactory.hpp"
#include "MapBuilder.hpp"

#include "game/components/ComponentOnDeathEvent.class.hpp"
#include "game/components/ComponentScore.class.hpp"

#include "game/system/System.hpp"

#include "Core.hpp"


/* Instantiation **************************************************************/
Party::Party(void) = default;

Party::~Party(void) {
	this->_remove_all_entities();
}

/* Party methods ***************************************************************/
Party::t_dims Party::getDims(void) const{
	return (std::make_pair(this->_width, this->_height));
}

void Party::initGame(void) {
	EntityFactory::setRules(&this->ruleSet);
	MapBuilder::build(*this);
}

void Party::update(void) {
	System::Input::update(*this);
	System::Timer::update(*this);
	if (Core::mode != Core::eMode::GAME)
		return;

	System::Physics::update(*this);
	System::Render::update(*this);
}

void Party::addEntity(Entity * entity) {
	this->entityList.push_back(entity);
}

void Party::removeAllAndResize(size_t height, size_t width) {
	this->_remove_all_entities();
	this->_height = height;
	this->_width  = width;
}

void Party::popEntity(Entity * entity) {
	if (std::find(this->entityList.begin(), this->entityList.end(), entity) != this->entityList.end()) {
		auto * c_onDeathEvent = entity->getComponent<ComponentOnDeathEvent>();

		if (c_onDeathEvent != nullptr) {
			c_onDeathEvent->execute(*this, entity);
		}
		this->entityList.remove(entity);
		delete entity;
	}
}

void Party::popEntity(t_entity_id id) {
	this->entityList.remove_if([&](Entity * entity) {
		if (entity->id == id) {
			auto * c_onDeathEvent = entity->getComponent<ComponentOnDeathEvent>();

			if (c_onDeathEvent != nullptr) {
				c_onDeathEvent->execute(*this, entity);
			}
			delete entity;
			return true;
		}
		return false;
	});
}

void Party::_remove_all_entities(void) {
	// delete all elements and clear the list
	// using remove if because it allows us to delete the inner entity
	if (!this->entityList.empty()) {
		this->entityList.remove_if([](Entity * entity) {
			delete entity;
			return true;
		});
	}
	this->_deletedEntityList.clear();
}

void Party::destroyEntity(Entity * entity) {
	this->_deletedEntityList.insert(entity);
}

void Party::removeDestroyedEntities(void) {
	if (!this->_deletedEntityList.empty()) {
		std::for_each(this->_deletedEntityList.begin(), this->_deletedEntityList.end(), [this](Entity * elem) {
			this->popEntity(elem);
		});

		this->_deletedEntityList.clear();
	}
}

size_t Party::getScore() const{
	Entity * entity = nullptr;

	for (auto * elem : this->entityList) {
		if (elem->getComponent<ComponentScore>() != nullptr) {
			entity = elem;
			break;
		}
	}
	if (entity == nullptr) {
		return 0;
	}
	return entity->getComponent<ComponentScore>()->value;
}
