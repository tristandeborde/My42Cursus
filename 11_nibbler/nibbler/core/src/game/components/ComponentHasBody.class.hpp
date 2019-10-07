#ifndef COMPONENTHASBODY_CLASS_HPP
#define	COMPONENTHASBODY_CLASS_HPP

#include <list>

#include "IComponent.class.hpp"

class Entity;
class Party;

class ComponentHasBody: public IComponent
{
	/* Instantiation **************************************************************/
	public:
		ComponentHasBody(void);
		~ComponentHasBody(void) override;

	/* Attributs ******************************************************************/
	private:
		// When the body grow, the body part must be add during movement (moveBody()).
		// We temporarily store the new body in this list.
		std::list<Entity *> _newBodyList;

	public:
		std::list<Entity *> entityList;

		void moveBody(Entity * head, Party & party);
		void addBody(void);

		void calculateSprite(Entity * head);

		eComponentType getType(void) const noexcept override;

	/* Compliant methods **********************************************************/
	public:
		ComponentHasBody(const ComponentHasBody &) = delete;
		ComponentHasBody & operator=(const ComponentHasBody &) = delete;
};

#endif	// COMPONENTHASBODY_CLASS_HPP
