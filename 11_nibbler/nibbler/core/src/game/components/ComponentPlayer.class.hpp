#ifndef COMPONENTPLAYER_CLASS_HPP
#define	COMPONENTPLAYER_CLASS_HPP

#include "IComponent.class.hpp"
#include "Vector2.class.hpp"

class ComponentPlayer: public IComponent
{
	/* Instantiation **************************************************************/
	public:
		ComponentPlayer(void);
		~ComponentPlayer(void) override;

		eComponentType getType(void) const noexcept override;

	/* Compliant methods **********************************************************/
	public:
		ComponentPlayer(const ComponentPlayer &) = delete;
		ComponentPlayer & operator=(const ComponentPlayer &) = delete;
};

#endif	// COMPONENTPLAYER_CLASS_HPP
