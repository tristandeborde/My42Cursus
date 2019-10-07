#ifndef OPENGL_CLASS_HPP
#define	OPENGL_CLASS_HPP

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
#include "Renderer.class.hpp"

class Opengl
{
	/* Singleton Methods **********************************************************/
	private:
		static Opengl * _inst;

	public:
		static Opengl * get(void);

	/* Instantiation **************************************************************/
	public:
		~Opengl(void)		  = default;
		Opengl(const Opengl&) = delete;
		Opengl& operator=(const Opengl&) = delete;

	private:
		Opengl(void) = default;


	/* Opengl Methods *************************************************************/
	public:
		void			begin(void);
		void			end(void);
		void			drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score);
		void			drawmenu(t_menu menu);
		t_input			input(void);
		void			resetSize(void);
		const char * getlog(void);
		void			log(const std::string &msg);
		void			log(const std::string &msg, eMsgType err);

	private:
		void			initModels(void);
		void			_rotateSnake(t_case type, Entity3d &entity);

	/* Attributes *****************************************************************/
	private:
		Renderer _renderer {};
		bool _ingame {false};
		t_menu _menu {};
		uint64_t _sel_button {0};
		std::map<t_case, t_model> _mapCase {};
		std::map<t_model, ModelConfig> _mapModel {};
		std::map<std::string, Model> _mapButton {};
		std::deque<std::string>	_logs {};
		double _score_last_time {0};
		uint32_t _score_last {0};
};

#endif	// #ifndef OPENGL_CLASS_HPP
