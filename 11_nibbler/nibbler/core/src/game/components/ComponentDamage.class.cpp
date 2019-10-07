#include "ComponentDamage.class.hpp"

/* Instantiation **************************************************************/

ComponentDamage::ComponentDamage(unsigned int _damage)
	: damage(_damage)
{}

ComponentDamage::~ComponentDamage(void) = default;


/* Attributs ******************************************************************/

eComponentType ComponentDamage::getType(void) const noexcept {
	return eComponentType::Damage;
}
