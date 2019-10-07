#ifndef GAMECLOCK_CLASS_HPP
#define	GAMECLOCK_CLASS_HPP

#include <chrono>

class GameClock
{
	/* Typedefs *******************************************************************/
	public:
		using t_clock	  = std::chrono::steady_clock;
		using t_duration  = t_clock::duration;
		using t_timepoint = std::chrono::time_point<t_clock>;

	/* Instantiation **************************************************************/
	public:
		GameClock();
		~GameClock() = default;

	/* Clock interface ************************************************************/
	public:
		t_timepoint			now(void) const;
		void				pause(void);
		void				resume(void);

	/* Attributes *****************************************************************/
	private:
		t_duration _offset;
		t_timepoint	_pause_time;
		bool _isPaused{false};

	/* Coplien funcs **************************************************************/
	public:
		GameClock & operator=(GameClock const &src) = delete;
		GameClock(GameClock const &src) = delete;
};

#endif	// GAMECLOCK_CLASS_HPP
