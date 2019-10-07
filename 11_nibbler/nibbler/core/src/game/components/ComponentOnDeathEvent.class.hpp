#ifndef COMPONENTONDEATHEVENT_CLASS_HPP
#define	COMPONENTONDEATHEVENT_CLASS_HPP

#include "IComponent.class.hpp"
#include <functional>

class Party;
class Entity;

class ComponentOnDeathEvent: public IComponent
{
	using t_event =	std::function<void(Party & party, Entity * entity)>;

	/* Instantiation **************************************************************/
	public:
		explicit ComponentOnDeathEvent(t_event event);
		~ComponentOnDeathEvent(void) override;

	/* Attributs ******************************************************************/
	private:
		const t_event _event;

	public:
		void		execute(Party & party, Entity * entity) const;

		eComponentType getType(void) const noexcept override;

	/* Compliant methods **********************************************************/
	public:
		ComponentOnDeathEvent() = delete;
		ComponentOnDeathEvent(const ComponentOnDeathEvent &) = delete;
		ComponentOnDeathEvent & operator=(const ComponentOnDeathEvent &) = delete;
};

#endif	// COMPONENTONDEATHEVENT_CLASS_HPP
