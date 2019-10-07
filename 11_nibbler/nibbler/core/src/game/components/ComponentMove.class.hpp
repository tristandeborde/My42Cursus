#ifndef COMPONENTMOVE_CLASS_HPP
#define	COMPONENTMOVE_CLASS_HPP

#include "IComponent.class.hpp"
#include "Vector2.class.hpp"

#include "game/clocks/GameClock.class.hpp"

class ComponentMove: public IComponent
{
	/* Instantiation **************************************************************/
	public:
		ComponentMove(void);
		ComponentMove(const Vector2f &_direction, float _speed);
		~ComponentMove(void) override;

	/* Attributs ******************************************************************/
	private:
		GameClock::t_timepoint _lastMove;

	public:
		Vector2f direction{0.f, 0.f};
		float speed{1.f};	// Number of movement per second

		bool canMove(GameClock::t_timepoint now);
		eComponentType getType(void) const noexcept override;

	/* Compliant methods **********************************************************/
	public:
		ComponentMove(const ComponentMove &) = delete;
		ComponentMove & operator=(const ComponentMove &) = delete;
};

#endif	// COMPONENTMOVE_CLASS_HPP
