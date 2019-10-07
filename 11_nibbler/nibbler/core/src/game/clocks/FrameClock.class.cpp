#include <thread>

#include "FrameClock.class.hpp"

/* Instantiation *************************************************************/
FrameClock::FrameClock() {
	this->init();
}

/* Clock Interface ************************************************************/
void FrameClock::init() {
	this->_start = t_clock::now();
}

void FrameClock::wait() const{
	const std::chrono::nanoseconds dura = t_clock::now() - this->_start;

	const std::chrono::milliseconds frame{1000 / FPS};
	const std::chrono::milliseconds elapsed_millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(dura);

	if (frame <= elapsed_millisecond)
		return;

	std::this_thread::sleep_for(frame - elapsed_millisecond);
}
