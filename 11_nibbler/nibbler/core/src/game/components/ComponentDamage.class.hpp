#ifndef COMPONENTDAMAGE_CLASS_HPP
#define	COMPONENTDAMAGE_CLASS_HPP

#include "IComponent.class.hpp"

class ComponentDamage: public IComponent
{
	/* Instantiation **************************************************************/
	public:
		explicit ComponentDamage(unsigned int _damage);
		~ComponentDamage(void) override;

	/* Attributs ******************************************************************/
	public:
		unsigned int damage;

		eComponentType getType(void) const noexcept override;

	/* Compliant methods **********************************************************/
	public:
		ComponentDamage() = delete;
		ComponentDamage(const ComponentDamage &) = delete;
		ComponentDamage & operator=(const ComponentDamage &) = delete;
};

#endif	// COMPONENTDAMAGE_CLASS_HPP
