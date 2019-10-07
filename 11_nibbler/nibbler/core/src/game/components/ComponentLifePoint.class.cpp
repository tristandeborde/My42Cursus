#include "ComponentLifePoint.class.hpp"

/* Instantiation **************************************************************/

ComponentLifePoint::ComponentLifePoint(unsigned int maxHP)
	: _maxHP(maxHP), _currentHP(static_cast<int>(maxHP))
{}

ComponentLifePoint::~ComponentLifePoint(void) = default;

/* Attributs ******************************************************************/

int	ComponentLifePoint::getCurrentHP(void) const{
	return this->_currentHP;
}

void ComponentLifePoint::addHP(int hp) {
	this->_currentHP += hp;

	if (this->_currentHP > static_cast<int>(this->_maxHP))
		this->_currentHP = static_cast<int>(this->_maxHP);
}

void ComponentLifePoint::subHP(int hp) {
	this->_currentHP -= hp;

	if (this->_currentHP < 0)
		this->_currentHP = 0;
}

bool ComponentLifePoint::isDead() const{
	return this->_currentHP == 0;
}

eComponentType ComponentLifePoint::getType(void) const noexcept {
	return eComponentType::LifePoint;
}
