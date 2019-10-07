#ifndef MENU_CLASS_HPP
#define	MENU_CLASS_HPP

#include <vector>
#include <string>
#include <functional>
#include "libmedia_interface.hpp"
#include "Button.class.hpp"


class Menu
{
	using t_callback = std::function<void(void)>;

	/* Instantiation **************************************************************/
	public:
		Menu(void) = default;
		Menu(Menu const &src);
		~Menu(void);

		Menu  &operator=(Menu const &rhs);

	/* Menu methods ***************************************************************/
	public:
		// these methods change the configuration of the menu before we render it.
		void	initMainMenu(void);
		void	initPauseMenu(void);
		void	initGameOverMenu(void);
		void	initMainSettingsMenu(void);
		void	initPauseSettingsMenu(void);

		// render the menu and wait for input.
		void	update(void);

	private:
		void	_initSettingsMenuCommon(void);

		// delete all previous menu data.
		void	_clear(void);
		// render the menu.
		void	_drawMenu(void) const;

	/* Attributes *****************************************************************/
	private:
		std::vector<Button *> _buttonList;
		t_callback _esc_callback;
		std::string	_title;
};

#endif	// MENU_CLASS_HPP
