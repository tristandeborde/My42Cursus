#ifndef RENDERER_CLASS_HPP
#define	RENDERER_CLASS_HPP

#include <ncurses.h>
#include "libmedia_interface.hpp"

#include <map>


class Renderer
{
	/* Typedefs *******************************************************************/
	using KeyValue	   = int;
	using EntitySymbol = char;

	enum class		eMode{
		GAME,
		MENU
	};

	/* Instantiation **************************************************************/
	public:
		Renderer();
		~Renderer();

	/* Renderer Methods ***********************************************************/
	public:
		void			drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score);
		void			drawmenu(t_menu menu);

		t_input			input(void);

		const char * getlog(void);

	/* Input matching *************************************************************/
	private:
		std::map<t_case, EntitySymbol> _caseMap;
		std::map<KeyValue, t_game_action> _gameActionMap;

		EntitySymbol	_getEntitySymbol(t_case type) const;
		bool			_checkKeyforGameAction(KeyValue key) const;
		t_game_action	_getGameAction(KeyValue key) const;

	/* Mode management ************************************************************/
	private:
		eMode _currentMode{eMode::MENU};
		size_t _buttonNumber{0};
		t_id _selectedButton{0};


	/* Coplien Methods ************************************************************/
	public:
		Renderer(Renderer const &src) = delete;
		Renderer  &operator=(Renderer const &rhs) = delete;
};

#endif	// RENDERER_CLASS_HPP
