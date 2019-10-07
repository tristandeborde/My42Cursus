#include "Renderer.class.hpp"
#include <cstring>
#include <string>

Renderer::Renderer() {
	// ncurses initialization
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	timeout(0);
	keypad(stdscr, TRUE);

	// maps initialization
	this->_caseMap[EMPTY]			 = ' ';
	this->_caseMap[WALL]			 = 'X';
	this->_caseMap[PLAYER]			 = '8';
	this->_caseMap[BOMB]			 = 'B';
	this->_caseMap[FRUIT]			 = 'O';
	this->_caseMap[EXPLOSION]		 = '#';
	this->_caseMap[SNAKE_HEAD_UP]	 = '%';
	this->_caseMap[SNAKE_HEAD_RIGHT] = '%';
	this->_caseMap[SNAKE_HEAD_DOWN]	 = '%';
	this->_caseMap[SNAKE_HEAD_LEFT]	 = '%';
	this->_caseMap[SNAKE_TAIL_UP]	 = '%';
	this->_caseMap[SNAKE_TAIL_RIGHT] = '%';
	this->_caseMap[SNAKE_TAIL_DOWN]	 = '%';
	this->_caseMap[SNAKE_TAIL_LEFT]	 = '%';
	this->_caseMap[SNAKE_UP_DOWN]	 = '%';
	this->_caseMap[SNAKE_RIGHT_LEFT] = '%';
	this->_caseMap[SNAKE_UP_RIGHT]	 = '%';
	this->_caseMap[SNAKE_RIGHT_DOWN] = '%';
	this->_caseMap[SNAKE_DOWN_LEFT]	 = '%';
	this->_caseMap[SNAKE_LEFT_UP]	 = '%';

	this->_gameActionMap[KEY_UP]	= t_game_action::GAME_UP;
	this->_gameActionMap[KEY_LEFT]	= t_game_action::GAME_LEFT;
	this->_gameActionMap[KEY_DOWN]	= t_game_action::GAME_DOWN;
	this->_gameActionMap[KEY_RIGHT] = t_game_action::GAME_RIGHT;
	this->_gameActionMap['b']		= t_game_action::GAME_DROP_BOMB;
}

Renderer::~Renderer() {
	endwin();
}

void Renderer::drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score) {
	if (this->_currentMode != eMode::GAME) {
		// clear the terminal because some chracters from the menu can stay when we render the game
		clear();
		this->_currentMode = eMode::GAME;
	}

	char ** map;
	// resizeterm(height, width);

	map = new char *[height];
	for (size_t i = 0; i < height; ++i)	{
		map[i] = new char[width];
		for (size_t j = 0; j < width; ++j)
			map[i][j] = this->_getEntitySymbol(EMPTY);
	}

	for (size_t i = 0; i < nb_items; ++i) {
		auto x = static_cast<size_t>(items[i].x);
		auto y = static_cast<size_t>(items[i].y);
		map[y][x] = this->_getEntitySymbol(items[i].type);
	}

	for (size_t i = 0; i < height; ++i)	{
		for (size_t j = 0; j < width; ++j)
			mvaddch(i, j, map[i][j]);
	}

	mvaddstr(height + 2, 0, "Score: ");
	addstr(std::to_string(score).c_str());
	refresh();

	for (size_t i = 0; i < height; ++i)
		delete[] map[i];
	delete[] map;
}	// Renderer::drawgame

void Renderer::drawmenu(t_menu menu) {
	if (this->_currentMode != eMode::MENU) {
		this->_currentMode = eMode::MENU;
	}
	this->_buttonNumber = menu.nb_buttons;

	clear();
	move(0, 0);
	addstr("## ncurses : ");
	addstr(menu.title);
	addstr(" ##");
	for (size_t i = 0; i < menu.nb_buttons; i++) {
		move(static_cast<int>(i) + 1, 0);
		addstr(i == this->_selectedButton ? "> " : "  ");
		addstr("  ");
		addstr(menu.li_buttons[i].title);
	}
	refresh();
}

t_input	Renderer::input(void) {
	t_input	input;
	KeyValue c;

	bzero(&input, sizeof(input));
	input.type = NO_INPUT;
	c = getch();


	if (c >= '1' && c <= '9') {
		input.type = RCHANGE;
		input.u_input_raw.rchange = c - '0';
	}
	else if (c == 27) {	// ECHAP
		input.type = ECHAP;
	}
	else if (this->_currentMode == eMode::MENU) {
		if (c == KEY_DOWN && this->_selectedButton < this->_buttonNumber - 1) {
			++this->_selectedButton;
		}
		else if (c == KEY_UP && this->_selectedButton > 0) {
			--this->_selectedButton;
		}
		else if (c == '\n')	{
			input.type = MENU;
			input.u_input_raw.menu = {MENU_CLICK, this->_selectedButton};
			// reset cursor position
			this->_selectedButton = 0;
		}
	}
	else if (this->_currentMode == eMode::GAME && this->_checkKeyforGameAction(c)) {
		input.type = GAME;
		input.u_input_raw.game = this->_getGameAction(c);
	}

	return (input);
}	// Renderer::input

const char * Renderer::getlog(void) {
	return nullptr;
}

Renderer::EntitySymbol Renderer::_getEntitySymbol(const t_case type) const{
	return this->_caseMap.at(type);
}

bool Renderer::_checkKeyforGameAction(KeyValue key) const{
	return this->_gameActionMap.find(key) != this->_gameActionMap.end();
}

t_game_action Renderer::_getGameAction(const KeyValue key) const{
	return this->_gameActionMap.at(key);
}
