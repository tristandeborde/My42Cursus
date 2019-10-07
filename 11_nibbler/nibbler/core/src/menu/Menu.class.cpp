#include <algorithm>

#include "Menu.class.hpp"
#include "Core.hpp"

#include "game/clocks/FrameClock.class.hpp"

#include "utils/GraphicsLoader.hpp"
#include "utils/Logger.hpp"

Menu::~Menu(void) {
	this->_clear();
}

Menu::Menu(Menu const &src) {
	*this = src;
}

Menu  &Menu::operator=(Menu const &rhs) {
	this->_title = rhs._title;

	this->_clear();
	for (auto * elem : rhs._buttonList)
		this->_buttonList.emplace_back(new Button(*elem));

	this->_esc_callback = rhs._esc_callback;

	return *this;
}

/* Menu methods ***************************************************************/
void Menu::initMainMenu(void) {
	this->_clear();

	this->_title = "BOMBLER";
	this->_buttonList.push_back(new Button([]() {
		Core::initGame();
		Core::setMode(Core::eMode::GAME);
	}, "Play"));

	// temporary remove parameters menu for Nibbler

	/*
	 * this->_buttonList.push_back(new Button([this]() {
	 *  Core::setMode(Core::eMode::MENU);
	 *  this->initMainSettingsMenu();
	 * }, "Settings"));
	 */

	auto exit_func = std::bind(Core::setMode, Core::eMode::EXIT);
	this->_buttonList.push_back(new Button(exit_func, "Exit"));
	this->_esc_callback = exit_func;
}

void Menu::_initSettingsMenuCommon(void) {
	this->_title = "SETTINGS";
	this->_buttonList.push_back(new Button(std::bind(Core::setMode, Core::eMode::EXIT), "Setting 1"));
	this->_buttonList.push_back(new Button(std::bind(Core::setMode, Core::eMode::EXIT), "Setting 2"));
}

void Menu::initMainSettingsMenu(void) {
	this->_clear();
	this->_initSettingsMenuCommon();

	this->_buttonList.push_back(new Button(std::bind(&Menu::initMainMenu, this), "..."));
	this->_esc_callback = std::bind(&Menu::initMainMenu, this);
}

void Menu::initPauseSettingsMenu(void) {
	this->_clear();
	this->_initSettingsMenuCommon();

	this->_buttonList.push_back(new Button(std::bind(&Menu::initPauseMenu, this), "..."));
	this->_esc_callback = std::bind(&Menu::initPauseMenu, this);
}

void Menu::initPauseMenu(void) {
	this->_clear();

	this->_title = "PAUSE";
	this->_buttonList.push_back(new Button(std::bind(Core::setMode, Core::eMode::GAME), "Resume"));

	// temporary remove parameters menu for Nibbler

	/*
	 * this->_buttonList.push_back(new Button([this]() {
	 *  Core::setMode(Core::eMode::MENU);
	 *  this->initPauseSettingsMenu();
	 * }, "Settings"));
	 */

	auto main_func = [this]() {
		  Core::setMode(Core::eMode::MENU);
		  this->initMainMenu();
	  };
	this->_buttonList.push_back(new Button(main_func, "Main Menu"));
	this->_esc_callback = main_func;
}

void Menu::initGameOverMenu(void) {
	this->_clear();

	this->_title = "GAME OVER";
	auto main_func = [this]() {
		  Core::setMode(Core::eMode::MENU);
		  this->initMainMenu();
	  };

	this->_buttonList.push_back(new Button([]() {}, "Score: " + std::to_string(Core::getScore())));
	this->_buttonList.push_back(new Button(main_func, "Main Menu"));
	this->_esc_callback = main_func;
}

void Menu::update(void) {
	t_input	input = GraphicsLoader::libmedia_input();

	if (input.type == MENU)	{
		t_menu_input action = input.u_input_raw.menu;

		if (action.act == t_menu_action::MENU_CLICK) {
			this->_buttonList[action.bid]->action();
			return;
		}
	}
	else if (input.type == ECHAP) {
		this->_esc_callback();
		return;
	}
	else if (input.type == EXIT) {
		Core::setMode(Core::eMode::EXIT);
	}

	this->_drawMenu();
}

void Menu::_clear(void) {
	// delete all elements and clear the list
	if (!this->_buttonList.empty()) {
		std::for_each(this->_buttonList.begin(), this->_buttonList.end(), [](Button * button) {
			delete button;
		});
		this->_buttonList.clear();
	}
	this->_esc_callback = []() {};
}

void Menu::_drawMenu(void) const{
	t_menu menu;

	menu.li_buttons = new t_button[this->_buttonList.size()];
	for (size_t i = 0; i < this->_buttonList.size(); ++i)
		menu.li_buttons[i] = this->_buttonList[i]->serialize();

	menu.nb_buttons = this->_buttonList.size();
	menu.title		= this->_title.c_str();

	GraphicsLoader::libmedia_drawmenu(menu);
	delete [] menu.li_buttons;
}
