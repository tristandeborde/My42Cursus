#include "ComponentTimerEvent.class.hpp"

/* Instantiation **************************************************************/

ComponentTimerEvent::ComponentTimerEvent(GameClock::t_duration threshold, t_event event)
	: _threshold(threshold), _event(std::move(event)) {
	this->startTimer();
}

ComponentTimerEvent::~ComponentTimerEvent(void) = default;

/* Timer Method ***************************************************************/

void ComponentTimerEvent::startTimer(void) {
	this->_start = Core::clock->now();
}

/* Attributs ******************************************************************/

GameClock::t_duration ComponentTimerEvent::getElapsedTime(GameClock::t_timepoint now) const{
	GameClock::t_duration elapsed = now - this->_start;

	return elapsed;
}

bool ComponentTimerEvent::isFinished(GameClock::t_timepoint now) const{
	if (this->getElapsedTime(now) > this->_threshold)
		return true;

	return false;
}

void ComponentTimerEvent::execute(Party & party, Entity * entity) const{
	this->_event(party, entity);
}

eComponentType ComponentTimerEvent::getType(void) const noexcept {
	return eComponentType::TimerEvent;
}
