#include "ComponentScore.class.hpp"

/* Instantiation **************************************************************/

ComponentScore::~ComponentScore(void) = default;

/* Attributs ******************************************************************/

eComponentType ComponentScore::getType(void) const noexcept {
	return eComponentType::Score;
}
