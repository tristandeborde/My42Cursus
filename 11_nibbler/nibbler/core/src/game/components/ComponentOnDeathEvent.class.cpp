#include "ComponentOnDeathEvent.class.hpp"

/* Instantiation **************************************************************/

ComponentOnDeathEvent::ComponentOnDeathEvent(t_event event)
	: _event(std::move(event))
{}

ComponentOnDeathEvent::~ComponentOnDeathEvent(void) = default;


/* Attributs ******************************************************************/

void ComponentOnDeathEvent::execute(Party & party, Entity * entity) const{
	this->_event(party, entity);
}

eComponentType ComponentOnDeathEvent::getType(void) const noexcept {
	return eComponentType::OnDeathEvent;
}
