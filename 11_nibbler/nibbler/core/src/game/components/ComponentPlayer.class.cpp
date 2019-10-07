#include "ComponentPlayer.class.hpp"

/* Instantiation **************************************************************/

ComponentPlayer::ComponentPlayer(void) = default;

ComponentPlayer::~ComponentPlayer(void) = default;

eComponentType ComponentPlayer::getType(void) const noexcept {
	return eComponentType::Player;
}
