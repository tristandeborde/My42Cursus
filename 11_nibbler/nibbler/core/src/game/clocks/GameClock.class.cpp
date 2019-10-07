#include "GameClock.class.hpp"

/* Instantiation *************************************************************/
GameClock::GameClock() : _offset(0), _pause_time(t_clock::now())
{}

/* Func group 1 **************************************************************/
GameClock::t_timepoint GameClock::now(void) const{
	return (t_clock::now() - this->_offset);
}

void GameClock::pause(void) {
	if (!this->_isPaused) {
		this->_pause_time = t_clock::now();
		this->_isPaused	  = true;
	}
}

void GameClock::resume(void) {
	if (this->_isPaused) {
		this->_offset  += t_clock::now() - this->_pause_time;
		this->_isPaused = false;
	}
}
