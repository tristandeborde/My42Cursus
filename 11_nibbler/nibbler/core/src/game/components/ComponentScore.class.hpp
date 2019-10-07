#ifndef COMPONENTSCORE_CLASS_HPP
#define	COMPONENTSCORE_CLASS_HPP

#include <cstdint>

#include "IComponent.class.hpp"

class ComponentScore: public IComponent
{
	/* Instantiation **************************************************************/
	public:
		ComponentScore(void) = default;
		~ComponentScore(void) override;

	/* Attributs ******************************************************************/
	public:
		uint32_t value {0};

		eComponentType	getType(void) const noexcept override;

	/* Compliant methods **********************************************************/
	public:
		ComponentScore(const ComponentScore &) = delete;
		ComponentScore & operator=(const ComponentScore &) = delete;
};

#endif	// COMPONENTSCORE_CLASS_HPP
