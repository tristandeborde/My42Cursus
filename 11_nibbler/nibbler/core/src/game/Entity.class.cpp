#include "Entity.class.hpp"

/* Instantiation **************************************************************/

Entity::Entity(t_entity_id _id, Vector2f _pos, Vector2f _size) :
	id(_id),
	pos(std::move(_pos)),
	size(std::move(_size))
{}

Entity::~Entity() {
	while (!_components.empty()) {
		delete _components.back();
		_components.pop_back();
	}
}

/* Entity methods *************************************************************/

void Entity::addComponent(IComponent * component) {
	_components.push_back(component);
}
