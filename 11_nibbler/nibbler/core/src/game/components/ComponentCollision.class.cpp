#include "ComponentCollision.class.hpp"

/* Instantiation **************************************************************/

ComponentCollision::ComponentCollision(eCollisionType _collisionType, t_collision_event event)
	: collisionType(_collisionType), _event(std::move(event))
{}

ComponentCollision::~ComponentCollision(void) = default;

/* Attributs ******************************************************************/

eComponentType ComponentCollision::getType(void) const noexcept {
	return eComponentType::Collision;
}

bool ComponentCollision::hasCollisionEvent(void) const noexcept {
	return this->_event != nullptr;
}

void ComponentCollision::execute(Party & party, Entity * entity) {
	if (this->hasCollisionEvent() && !this->_event_is_executed) {
		this->_event(party, entity);
		this->_event_is_executed = true;
	}
}
