#ifndef COMPONENTTIMEREVENT_CLASS_HPP
#define	COMPONENTTIMEREVENT_CLASS_HPP

#include <chrono>
#include <functional>

#include "IComponent.class.hpp"

#include "Core.hpp"

#include "game/clocks/GameClock.class.hpp"

class Party;
class Entity;

class ComponentTimerEvent: public IComponent
{
	public:
		using t_event = std::function<void(Party & party, Entity * entity)>;

	/* Instantiation **************************************************************/
	public:
		ComponentTimerEvent(GameClock::t_duration threshold, t_event event);
		~ComponentTimerEvent(void) override;

	/* Attributs ******************************************************************/
	private:
		const GameClock::t_duration _threshold;
		GameClock::t_timepoint _start;
		t_event _event;

	/* Timer Method ***************************************************************/
	public:
		void					startTimer(void);
		GameClock::t_duration	getElapsedTime(GameClock::t_timepoint now) const;
		bool					isFinished(GameClock::t_timepoint now) const;

		void					execute(Party & party, Entity * entity) const;

		eComponentType getType(void) const noexcept override;

	/* Compliant methods **********************************************************/
	public:
		ComponentTimerEvent(void) = delete;
		ComponentTimerEvent(const ComponentTimerEvent &) = delete;
		ComponentTimerEvent & operator=(const ComponentTimerEvent &) = delete;
};

#endif	// COMPONENTTIMEREVENT_CLASS_HPP
