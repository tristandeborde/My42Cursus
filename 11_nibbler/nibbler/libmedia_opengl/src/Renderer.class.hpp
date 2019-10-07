#ifndef RENDERER_CLASS_HPP
#define	RENDERER_CLASS_HPP

#include <string>
#include <deque>
#include <map>

#include "libmedia_opengl.h"

#include "Config.hpp"
#include "Shader.class.hpp"
#include "Model.class.hpp"
#include "ModelConfig.class.hpp"
#include "Camera.class.hpp"
#include "Entity3d.class.hpp"
#include "Model.class.hpp"
#include "Exception.class.hpp"

class Renderer
{
	/* Singleton Methods **********************************************************/
	private:
		static Renderer * _inst;

	public:
		static Renderer * get(void);

	/* Instantiation **************************************************************/
	public:
		Renderer(void) = default;
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		~Renderer(void) = default;


	/* Renderer Methods ***********************************************************/
	public:
		void			init(void);
		void			end(void);

		void			addEntity(Entity3d &entity);
		void			resetSize(void);

		void			render(void);
		void			renderGame(size_t width);
		void			renderMenu(size_t nb_buttons);

		float			distToCamera(glm::vec3 pos);

	private:
		void _initShadow(void);

		void _renderShadow(void);
		void _renderEntities(Shader shader);
		void _renderHud(uint32_t score);


	/* Attributes *****************************************************************/
	public:
		float settings[4] {0.0f, -17.0f, 23.0f, 40.0f};

	private:
		SDL_Window * _win {nullptr};
		SDL_GLContext _glcontext {};
		Shader _shader {};
		Shader _game_shader {};
		Shader _shadow_shader {};
		Camera _camera {};
		Camera _light {};
		std::vector<Entity3d> _entities {};
		uint32_t _depth_map {0};
		uint32_t _depth_map_fbo {0};
};

int	eventAddedCallback(void * data, SDL_Event * event);
bool compareDistToCamera(Entity3d i1, Entity3d i2);

#endif	// #ifndef RENDERER_CLASS_HPP
