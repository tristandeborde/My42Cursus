#include "ComponentMove.class.hpp"

/* Instantiation **************************************************************/

ComponentMove::ComponentMove(void) = default;

ComponentMove::ComponentMove(const Vector2f &_direction, float _speed)
	: direction(_direction), speed(_speed)
{}

ComponentMove::~ComponentMove(void) = default;

/* Attributs ******************************************************************/

bool ComponentMove::canMove(GameClock::t_timepoint now) {
	const auto lapsBeforeMove = std::chrono::duration<float>(1.f / this->speed);

	if (now - this->_lastMove >= lapsBeforeMove) {
		this->_lastMove = now;
		return true;
	}
	return false;
}

eComponentType ComponentMove::getType(void) const noexcept {
	return eComponentType::Move;
}
