#include <iostream>
#include <cstring>

#include "Renderer.class.hpp"
#include "Opengl.class.hpp"
#include "Exception.class.hpp"

constexpr char shaderVPath[]	   = "libmedia_opengl/shaders/shader.vs";
constexpr char shaderFPath[]	   = "libmedia_opengl/shaders/shader.fs";
constexpr char shadowShaderVPath[] = "libmedia_opengl/shaders/shadow_shader.vs";
constexpr char shadowShaderFPath[] = "libmedia_opengl/shaders/shadow_shader.fs";
constexpr char gameShaderVPath[]   = "libmedia_opengl/shaders/game_shader.vs";
constexpr char gameShaderFPath[]   = "libmedia_opengl/shaders/game_shader.fs";
constexpr int winWidthDefault	   = 1024;
constexpr int winHeightDefault	   = 1024;

Renderer * Renderer::_inst = nullptr;

Renderer         * Renderer::get(void) {
	if (Renderer::_inst == nullptr) {
		Renderer::_inst = new Renderer();
	}
	return Renderer::_inst;
}

void Renderer::init(void) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Opengl::get()->log("Error SDL_RenderCopy : ", eMsgType::SDLError);
		return;
	}	// Init SDL
	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
		Opengl::get()->log("Error IMG_Init : ", eMsgType::SDLError);
		return;
	}	// Init SDL_img
	if (TTF_Init() == -1) {
		Opengl::get()->log("TTF_Init : ", eMsgType::SDLError);
		return;
	}	// Init SDL_ttf
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// Create Window
	this->_win = SDL_CreateWindow("Bombler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidthDefault,
			winHeightDefault,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	// TODO(someone) exception management
	if (this->_win == nullptr) {
		Opengl::get()->log("Error SDL_CreateWindow : ", eMsgType::SDLError);
		return;
	}
	SDL_RaiseWindow(this->_win);// No error

	// Bind OpenGl to window
	this->_glcontext = SDL_GL_CreateContext(this->_win);
	if (this->_glcontext == nullptr) {
		Opengl::get()->log("Error SDL_GL_CreateContext : ", eMsgType::SDLError);
		return;
	}
	// glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	// glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Init opengl utils -> glew, glfw
	glewExperimental = 1u;
	if (glewInit() != GLEW_OK) {
		Opengl::get()->log("Error glewInit : ", eMsgType::OpenGLError);
		return;
	}
	if ((glfwInit()) == 0) {
		Opengl::get()->log("Error glfwInit : ", eMsgType::OpenGLError);
		return;
	}

	// Load Shaders
	try
	{
		this->_shader = Shader((std::string(BASEPATH) + "/" + shaderVPath).c_str(), (std::string(
				BASEPATH) + "/" + shaderFPath).c_str());
		this->_shadow_shader = Shader((std::string(BASEPATH) + "/" + shadowShaderVPath).c_str(), (std::string(
				BASEPATH) + "/" + shadowShaderFPath).c_str());
		this->_game_shader = Shader((std::string(BASEPATH) + "/" + gameShaderVPath).c_str(), (std::string(
				BASEPATH) + "/" + gameShaderFPath).c_str());
	}
	catch (const Exception& e)
	{
		Opengl::get()->log(e.what(), eMsgType::OpenGLError);
		return;
	}
	this->_game_shader.use();
	this->_game_shader.setInt("diffuseTexture", 0);
	this->_game_shader.setInt("shadowMap", 1);

	// Init shadow
	this->_initShadow();
}	// Renderer::begin

void Renderer::end(void) {
	glfwTerminate();
	SDL_GL_DeleteContext(this->_glcontext);
	SDL_DestroyWindow(this->_win);
	this->_shader.stop();
	this->_shadow_shader.stop();
	this->_game_shader.stop();
	glfwTerminate();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	/* Delete instance */
	if (Renderer::_inst != nullptr) {
		delete Renderer::_inst;
		Renderer::_inst = nullptr;
	}
}

void Renderer::renderGame(size_t width) {
	int win_width, win_height;
	float fov = 40.0f, angle = 45.0f;
	float d, x, y, z;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	SDL_GetWindowSize(this->_win, &win_width, &win_height);

	this->_light.setPos(15.0f, -15.0f, 15.0f);
	this->_light.setTarget(0.0f, 0.0f, 0.0f);

	d = (width / 2.0f) / std::tan(glm::radians(fov / 2.0f));
	d = d / 15.0f * 20.0f;
	x = 0.0f;
	y = -d * std::cos(glm::radians(angle));
	z = d * std::sin(glm::radians(angle));
	this->_camera.setPos(x, y, z);
	this->_camera.setTarget(0.0f, 0.0f, 0.0f);
	this->_camera.setProjectionPerspective(win_width, win_height, fov);

	this->_renderShadow();

	glViewport(0, 0, win_width, win_height);
	this->_renderEntities(this->_game_shader);
	this->_entities.clear();
	SDL_GL_SwapWindow(this->_win);
}

void Renderer::renderMenu(size_t nb_buttons) {
	int x, y;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	SDL_GetWindowSize(this->_win, &x, &y);

	this->_light.setPos(15.0f, 15.0f, 30.0f);
	this->_light.setTarget(0.0f, 0.0f, 0.0f);
	this->_camera.setPos(x < y ? 30.0f * 1024 / x : 30.0f, 0.0f, (nb_buttons + 1.0f) / 2.0f + 1.0f);
	this->_camera.setTarget(0.0f, 0.0f, (nb_buttons + 1.0f) / 2.0f + 1.0f);
	this->_camera.setProjectionPerspective(x, y, 40.0f);

	glViewport(0, 0, x, y);
	this->_renderEntities(this->_shader);
	this->_entities.clear();
	SDL_GL_SwapWindow(this->_win);
}

void Renderer::_renderEntities(Shader shader) {
	shader.use();

	shader.setMat4("view", this->_camera.getView());
	shader.setVec3("pos", this->_camera.getPos());
	shader.setMat4("projection", this->_camera.getProjection());
	shader.setMat4("light_view", this->_light.getView());
	shader.setVec3("light_pos", this->_light.getPos());
	shader.setMat4("light_projection", this->_light.getProjection());	// TODO(blefeuvr)
	for (auto entity: this->_entities) {
		entity.draw(shader);
	}
}

void Renderer::addEntity(Entity3d &entity) {
	this->_entities.push_back(entity);
}

float Renderer::distToCamera(glm::vec3 pos) {
	return (glm::distance(pos, this->_camera.getPos()));
}

bool compareDistToCamera(Entity3d i1, Entity3d i2) {
	float d1 = Renderer::get()->distToCamera(i1.getPos());
	float d2 = Renderer::get()->distToCamera(i2.getPos());

	return (d1 < d2);
}

void Renderer::_initShadow() {
	constexpr unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	glGenFramebuffers(1, &(this->_depth_map_fbo));
	glGenTextures(1, &(this->_depth_map));
	glBindTexture(GL_TEXTURE_2D, this->_depth_map);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
	  SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = {1.0, 1.0, 1.0, 1.0};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, this->_depth_map_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->_depth_map, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::_renderShadow() {
	int x, y;

	SDL_GetWindowSize(this->_win, &x, &y);
	this->_light.setProjectionOrtho(x, y, 30.0f);
	x *= 4;
	y *= 4;
	glViewport(0, 0, x, y);

	glBindTexture(GL_TEXTURE_2D, this->_depth_map);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, x, y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glBindFramebuffer(GL_FRAMEBUFFER, this->_depth_map_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->_depth_map, 0);

	glClear(GL_DEPTH_BUFFER_BIT);
	this->_renderEntities(this->_shadow_shader);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->_depth_map);
}

void Renderer::_renderHud(uint32_t) {}
