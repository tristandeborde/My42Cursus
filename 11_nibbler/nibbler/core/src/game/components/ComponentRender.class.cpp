#include "ComponentRender.class.hpp"

/* Instantiation **************************************************************/

ComponentRender::ComponentRender(t_case c)
	: sprite(c)
{}

ComponentRender::~ComponentRender(void) = default;

/* Attributs ******************************************************************/

eComponentType ComponentRender::getType(void) const noexcept {
	return eComponentType::Render;
}
