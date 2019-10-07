#include <iostream>
#include <cstring>

#include "Opengl.class.hpp"
#include "Exception.class.hpp"

Opengl * Opengl::_inst = nullptr;

Opengl * Opengl::get(void) {
	if (Opengl::_inst == nullptr) {
		Opengl::_inst = new Opengl();
	}
	return Opengl::_inst;
}

void Opengl::initModels(void) {
	this->_mapCase[WALL] = WALL_MODEL;
	this->_mapCase[SNAKE_HEAD_UP]	 = SNAKE_HEAD_MODEL;
	this->_mapCase[SNAKE_HEAD_RIGHT] = SNAKE_HEAD_MODEL;
	this->_mapCase[SNAKE_HEAD_DOWN]	 = SNAKE_HEAD_MODEL;
	this->_mapCase[SNAKE_HEAD_LEFT]	 = SNAKE_HEAD_MODEL;
	this->_mapCase[SNAKE_TAIL_UP]	 = SNAKE_TAIL_MODEL;
	this->_mapCase[SNAKE_TAIL_RIGHT] = SNAKE_TAIL_MODEL;
	this->_mapCase[SNAKE_TAIL_DOWN]	 = SNAKE_TAIL_MODEL;
	this->_mapCase[SNAKE_TAIL_LEFT]	 = SNAKE_TAIL_MODEL;
	this->_mapCase[SNAKE_UP_DOWN]	 = SNAKE_LINE_MODEL;
	this->_mapCase[SNAKE_RIGHT_LEFT] = SNAKE_LINE_MODEL;
	this->_mapCase[SNAKE_UP_RIGHT]	 = SNAKE_CORNER_MODEL;
	this->_mapCase[SNAKE_RIGHT_DOWN] = SNAKE_CORNER_MODEL;
	this->_mapCase[SNAKE_DOWN_LEFT]	 = SNAKE_CORNER_MODEL;
	this->_mapCase[SNAKE_LEFT_UP]	 = SNAKE_CORNER_MODEL;
	this->_mapCase[BOMB]	  = BOMB_MODEL;
	this->_mapCase[FRUIT]	  = FRUIT_MODEL;
	this->_mapCase[EXPLOSION] = EXPLOSION_MODEL;

	this->_mapModel[WALL_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/box.obj"), 1.0f};
	this->_mapModel[PLAYER_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/robot.obj"), 0.1f};
	this->_mapModel[BOMB_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/bomb.obj"), 2.0f};
	this->_mapModel[FRUIT_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/banana.obj"), 4.0f};
	this->_mapModel[EXPLOSION_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/explosion.obj"), 0.45f};
	this->_mapModel[FLOOR_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/floor.obj"), 1.0f};
	this->_mapModel[GROUND_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/ground.obj"), 1.0f};
	this->_mapModel[BUTTON_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/button.obj"), 1.0f};
	this->_mapModel[SCORE_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/square.obj"), 2.0f};
	this->_mapModel[SNAKE_HEAD_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/snake_head_v2.obj"), 0.5f};
	this->_mapModel[SNAKE_LINE_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/snake_line.obj"), 0.5f};
	this->_mapModel[SNAKE_CORNER_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/snake_corner.obj"), 0.5f};
	this->_mapModel[SNAKE_TAIL_MODEL] =
	  ModelConfig{Model(std::string(BASEPATH) + "/libmedia_opengl/assets/models/snake_back.obj"), 0.5f};
}	// Opengl::initModels

void Opengl::begin(void) {
	this->log("Opengl::begin");

	this->_renderer.init();
	// Load models in GPU
	try {
		this->initModels();
	} catch (const Exception& e) {
		this->log(e.what(), eMsgType::OpenGLError);
		return;
	}
}	// Opengl::begin

void Opengl::end(void) {
	this->_renderer.end();
	this->log("Opengl::end");
	Config::end();
	this->_logs.clear();
	/* Delete instance */
	if (Opengl::_inst != nullptr) {
		delete Opengl::_inst;
		Opengl::_inst = nullptr;
	}
}

t_input Opengl::input(void) {
	t_input input;
	SDL_Event e;

	std::memset(&input, 0, sizeof(input));
	SDL_PollEvent(&e);
	input.type = NO_INPUT;
	if (e.type == SDL_KEYDOWN) {
		this->log("Opengl got input " + std::to_string(e.key.keysym.sym));
		if (e.type == SDL_KEYDOWN) {
			if (SDLK_ESCAPE == e.key.keysym.sym) {
				input.type = ECHAP;
				return input;
			}
			for (auto const &elem : *Config::get_map_keys()) {
				if (elem.second == e.key.keysym.sym) {
					input.type = RCHANGE;
					input.u_input_raw.rchange = elem.first;
					return input;
				}
			}
			if (this->_ingame) {
				for (auto const &elem : *Config::get_map_input()) {
					if (elem.second == e.key.keysym.sym) {
						input.type = GAME;
						input.u_input_raw.game = elem.first;
						return input;
					}
				}
				switch (e.key.keysym.sym) {
					case SDLK_u:
						this->_renderer.settings[3] += 2.0f;
						std::cout << "set3: " << this->_renderer.settings[3] << std::endl;
						break;
					case SDLK_j:
						this->_renderer.settings[3] -= 2.0f;
						std::cout << "set3: " << this->_renderer.settings[3] << std::endl;
						break;
					case SDLK_i:
						this->_renderer.settings[0] += 1.0f;
						std::cout << "set0: " << this->_renderer.settings[0] << std::endl;
						break;
					case SDLK_k:
						this->_renderer.settings[0] -= 1.0f;
						std::cout << "set0: " << this->_renderer.settings[0] << std::endl;
						break;
					case SDLK_o:
						this->_renderer.settings[1] += 1.0f;
						std::cout << "set1: " << this->_renderer.settings[1] << std::endl;
						break;
					case SDLK_l:
						this->_renderer.settings[1] -= 1.0f;
						std::cout << "set1: " << this->_renderer.settings[1] << std::endl;
						break;
					case SDLK_p:
						this->_renderer.settings[2] += 1.0f;
						std::cout << "set2: " << this->_renderer.settings[2] << std::endl;
						break;
					case SDLK_SEMICOLON:
						this->_renderer.settings[2] -= 1.0f;
						std::cout << "set2: " << this->_renderer.settings[2] << std::endl;
						break;
				}
			}
			else {
				switch (e.key.keysym.sym) {
					case SDLK_DOWN:
						this->_sel_button = (this->_sel_button + 1) % this->_menu.nb_buttons;
						break;
					case SDLK_UP:
						this->_sel_button = (this->_sel_button - 1) % this->_menu.nb_buttons;
						break;
					case SDLK_RETURN:
						input.type = MENU;
						input.u_input_raw.menu = {MENU_CLICK, this->_sel_button};
						this->_sel_button	   = 0;
						break;
				}
			}
		}
	}
	else if (e.type == SDL_WINDOWEVENT) {
		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			input.type = EXIT;
		}
	}
	while (SDL_PollEvent(&e) != 0) {}
	return input;
}	// Opengl::input

void Opengl::drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score) {
	Entity3d entity;
	ModelConfig model_conf;
	Model model;

	this->_ingame = true;

	// draw ground
	model_conf = this->_mapModel[GROUND_MODEL];
	for (size_t i = 0; i < width; i++) {
		for (size_t j = 0; j < height; j++) {
			entity = Entity3d(
					model_conf.model,
					(static_cast<float>(i) - (width - 1) / 2.0f) * 5.0f,
					(static_cast<float>(j) - (height - 1) / 2.0f) * 5.0f,
					-3.5f,
					5.0f
			);
			this->_renderer.addEntity(entity);
		}
	}

	// draw items
	for (size_t i = 0; i < nb_items; ++i) {
		model_conf = this->_mapModel[this->_mapCase[items[i].type]];
		entity	   = Entity3d(
				model_conf.model,
				items[i].x - (width - 1) / 2.0f,
				items[i].y - (height - 1) / 2.0f,
				0.0f,
				model_conf.size
		);
		if ((items[i].type & 0xC0) != 0)
			this->_rotateSnake(items[i].type, entity);
		if (items[i].type == FRUIT) {
			std::srand(static_cast<unsigned int>(items[i].x * items[i].y * 10));
			entity.rotate(static_cast<float>(glm::radians(std::fmod(std::rand(),
					180.0f) + 100.0 * glfwGetTime())), 0.0f, 0.0f, 1.0f);
		}
		this->_renderer.addEntity(entity);
	}
	// draw floor
	model_conf = this->_mapModel[FLOOR_MODEL];
	for (size_t i = 0; i < width; i++) {
		for (size_t j = 0; j < height; j++) {
			entity = Entity3d(
					model_conf.model,
					static_cast<float>(i) - (width - 1) / 2.0f,
					static_cast<float>(j) - (height - 1) / 2.0f,
					-1.0f,
					model_conf.size
			);
			this->_renderer.addEntity(entity);
		}
	}
	// draw score
	if (this->_score_last != score) {
		this->_score_last	   = score;
		this->_score_last_time = glfwGetTime();
	}
	model_conf = this->_mapModel[SCORE_MODEL];
	model	   = model_conf.model.withText(std::to_string(score), glm::vec3(1.0f, 1.0f, 1.0f));
	entity	   = Entity3d(
			model,
			(width - 1) / 2.0f * -1,
			(height - 1) / 2.0f * -1,
			2.0f,
			model_conf.size
	);
	entity.rotate(glm::radians(90.0f), 1.0f, 0.0f, 0.0f);
	entity.rotate(glm::radians(180.0f), 0.0f, 0.0f, 1.0f);
	entity.rotate(glm::radians(180.0f
			* std::max(
			1.0f - static_cast<float>(5.0 * (glfwGetTime() - this->_score_last_time)), 0.0f)), 1.0f, 0.0f, 0.0f);
	this->_renderer.addEntity(entity);

	// render
	this->_renderer.renderGame(width);
}	// Opengl::drawgame

void Opengl::drawmenu(t_menu menu) {
	this->_menu	  = menu;
	this->_ingame = false;

	ModelConfig button_model_conf = this->_mapModel[BUTTON_MODEL];
	Entity3d entity;
	Model model;
	float offset = 0.0f;
	std::string title;

	// draw buttons
	for (size_t i = menu.nb_buttons; i > 0; i--) {
		title = menu.li_buttons[i - 1].title;
		try {
			model = this->_mapButton.at(title);
		} catch (std::out_of_range &) {
			model = button_model_conf.model.withText(title, glm::vec3(0.0f, 0.0f, 0.0f));
			this->_mapButton[title] = model;
		}
		entity = Entity3d(model, 0.0f, 0.0f, offset, button_model_conf.size);
		// add selected effect
		if (i - 1 == this->_sel_button) {
			entity.rotate(glm::radians(5.0f),
			  0.0f,
			  static_cast<float>(glm::radians(1 * sin(5 * glfwGetTime()))),
			  static_cast<float>(glm::radians(1 * cos(5 * glfwGetTime())))
			);
		}
		this->_renderer.addEntity(entity);
		offset += 2.0f;
	}

	// draw title
	title = menu.title;
	try {
		model = this->_mapButton.at(title);
	} catch (std::out_of_range &) {
		model = button_model_conf.model.withText(title, glm::vec3(0.0f, 0.0f, 0.0f));
		this->_mapButton[title] = model;
	}
	entity = Entity3d(model, 0.0f, 0.0f, offset, button_model_conf.size);
	this->_renderer.addEntity(entity);

	// render
	this->_renderer.renderMenu(menu.nb_buttons);
}	// Opengl::drawmenu

void Opengl::_rotateSnake(t_case type, Entity3d &entity) {
	switch (type) {
		case SNAKE_HEAD_UP:
			entity.rotate(glm::radians(-90.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_HEAD_RIGHT:
			entity.rotate(glm::radians(180.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_HEAD_DOWN:
			entity.rotate(glm::radians(90.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_HEAD_LEFT:
			entity.rotate(glm::radians(0.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_TAIL_UP:
			entity.rotate(glm::radians(90.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_TAIL_RIGHT:
			entity.rotate(glm::radians(0.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_TAIL_DOWN:
			entity.rotate(glm::radians(-90.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_TAIL_LEFT:
			entity.rotate(glm::radians(180.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_UP_DOWN:
			entity.rotate(glm::radians(90.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_RIGHT_LEFT:
			entity.rotate(glm::radians(0.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_UP_RIGHT:
			entity.rotate(glm::radians(0.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_RIGHT_DOWN:
			entity.rotate(glm::radians(-90.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_DOWN_LEFT:
			entity.rotate(glm::radians(180.0f), 0.0f, 0.0f, 1.0f);
			break;
		case SNAKE_LEFT_UP:
			entity.rotate(glm::radians(90.0f), 0.0f, 0.0f, 1.0f);
			break;
		case EMPTY:
			break;
		case WALL:
			break;
		case PLAYER:
			break;
		case BOMB:
			break;
		case FRUIT:
			break;
		case EXPLOSION:
			break;
	}
}	// Opengl::_rotateSnake

void Opengl::log(const std::string &msg) {
	_logs.push_back(msg);
}

void Opengl::log(const std::string &msg, eMsgType err) {
	std::string	log = msg;
	GLenum gl_err;

	if (eMsgType::SDLError == err) {
		log.append(SDL_GetError());
		_logs.push_back(log);
	}
	else if (eMsgType::OpenGLError == err) {
		while ((gl_err = glGetError()) != GL_NO_ERROR) {
			_logs.push_back(log + "OpenGL error (" + std::to_string(gl_err) + ")");
		}
	}
	std::cout << log << std::endl;
}

const char	* Opengl::getlog(void) {
	const char * msg;

	if (_logs.empty() == false) {
		msg = _logs.front().c_str();
		_logs.pop_front();
	}
	else {
		return nullptr;
	}
	return msg;
}
