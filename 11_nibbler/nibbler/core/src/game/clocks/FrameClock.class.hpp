#ifndef FRAMECLOCK_CLASS_HPP
#define	FRAMECLOCK_CLASS_HPP

#include <chrono>

// Frame Per Second constant value
constexpr int FPS = 30;

class FrameClock
{
	/* Typedefs *******************************************************************/
	public:
		using t_clock	  = std::chrono::steady_clock;
		using t_timepoint = std::chrono::time_point<t_clock>;

	/* Instantiation **************************************************************/
	public:
		FrameClock();
		~FrameClock() = default;

	/* Clock Interface ************************************************************/
	public:
		void init();
		void wait() const;

	/* Attributes *****************************************************************/
	private:
		t_timepoint _start {};

	/* Coplien funcs **************************************************************/
	public:
		FrameClock & operator=(FrameClock const &src) = delete;
		FrameClock(FrameClock const &src) = delete;
};

#endif	// ifndef FRAMECLOCK_CLASS_HPP
