#include <stack>

#include "Core.hpp"

#include "game/clocks/FrameClock.class.hpp"

#include "game/Party.class.hpp"

#include "exceptions/CoreException.class.hpp"

namespace Core
{
	GameClock * clock = nullptr;
	Core::eMode mode{Core::eMode::MENU};
	namespace
	{
		Party * _gameEngine = nullptr;
		Menu * _menuEngine	= nullptr;
		bool _isInit		= false;
	}// namespace


	/* Core methods ***************************************************************/
	void	init(void) {
		_gameEngine = new Party();
		_menuEngine = new Menu();
		clock		= new GameClock();

		// init main menu
		_menuEngine->initMainMenu();

		_isInit = true;
	}

	void	end(void) {
		delete _gameEngine;
		_gameEngine = nullptr;

		delete _menuEngine;
		_menuEngine = nullptr;

		delete clock;
		clock = nullptr;

		_isInit = false;
	}

	void	start(void) {
		FrameClock frame_clock;

		if (!_isInit)
			throw CoreException("Core has not been initialized.");

		while (Core::mode != eMode::EXIT) {
			frame_clock.init();

			if (Core::mode == eMode::MENU)
				_menuEngine->update();
			else if (Core::mode == eMode::GAME || Core::mode == eMode::GAME_OVER)
				_gameEngine->update();

			frame_clock.wait();
		}
	}

	size_t getScore(void) {
		return Core::_gameEngine->getScore();
	}

	/* Callbacks methods **********************************************************/
	void	setMode(Core::eMode _mode) {
		if (_mode == Core::mode) {
			return;
		}

		if (_mode == eMode::GAME_OVER) {
			// pause Entity Timer
			Core::clock->pause();
			// after game over, we go to an intermediate menu that print out the score.
			_menuEngine->initGameOverMenu();
		}
		else if (_mode == eMode::GAME) {
			if (Core::mode == GAME_OVER) {	// check if the game is not already over
				return;
			}

			// resume Entity Timer
			Core::clock->resume();
			// init pause menu before the game start
			_menuEngine->initPauseMenu();
		}
		else if (_mode == eMode::MENU) {
			// pause Entity Timer
			Core::clock->pause();
		}

		Core::mode = _mode;
	}

	void	initGame() {
		_gameEngine->initGame();
	}
}// namespace Core
