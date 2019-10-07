#include "System.hpp"

#include "game/Party.class.hpp"
#include "game/components/ComponentTimerEvent.class.hpp"

namespace System {
	namespace Timer {
		void update(Party & party) {
			GameClock::t_timepoint now = Core::clock->now();

			for (auto * elem : party.entityList) {
				auto * c_timer = elem->getComponent<ComponentTimerEvent>();

				if (c_timer != nullptr && c_timer->isFinished(now)) {
					c_timer->execute(party, elem);
				}
			}

			party.removeDestroyedEntities();
		}
	}	// namespace Timer
}		// namespace System
