#ifndef COMPONENTRENDER_CLASS_HPP
#define	COMPONENTRENDER_CLASS_HPP

#include "IComponent.class.hpp"

#include "Vector2.class.hpp"
#include "libmedia_interface.hpp"

class ComponentRender: public IComponent
{
	/* Instantiation **************************************************************/
	public:
		explicit ComponentRender(t_case c = t_case::EMPTY);
		~ComponentRender(void) override;

	/* Attributs ******************************************************************/
	public:
		t_case sprite;

		eComponentType getType(void) const noexcept override;

	/* Compliant methods **********************************************************/
	public:
		ComponentRender(const ComponentRender &) = delete;
		ComponentRender & operator=(const ComponentRender &) = delete;
};

#endif	// COMPONENTRENDER_CLASS_HPP
