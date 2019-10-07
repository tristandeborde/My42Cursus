#ifndef CORE_HPP
#define	CORE_HPP

#include "menu/Menu.class.hpp"
#include "game/clocks/GameClock.class.hpp"

namespace Core
{
	enum eMode{
		EXIT = -1,
		GAME,
		GAME_OVER,
		MENU
	};
	extern Core::eMode mode;

	/* Core methods ***************************************************************/
	void	init(void);
	void	end(void);

	void	start(void);

	// temporary getScore() func for Nibbler
	size_t getScore(void);

	/* Callbacks methods **********************************************************/
	void	setMode(eMode _mode);
	void	initGame();

	/* Global Custom Clock ********************************************************/
	extern GameClock * clock;
}// namespace Core


#endif	// CORE_HPP
