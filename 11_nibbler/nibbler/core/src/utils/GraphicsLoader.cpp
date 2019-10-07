#include <map>
#include <dlfcn.h>

#include "GraphicsLoader.hpp"

#include "Logger.hpp"
#include "Core.hpp"

#include "exceptions/GraphicsLoaderException.class.hpp"

namespace GraphicsLoader
{
	namespace
	{
		eGraphicsType * _current_type = nullptr;
		void * _dl_image = nullptr;
		ILibMedia * (* _getLib)(void) = nullptr;
		ILibMedia * _libMediaInstance = nullptr;

		std::pair<bool, eGraphicsType> _assoc_rchange(int id) {
			if (id == 1)
				return std::make_pair(true, eGraphicsType::LIBMEDIA_NCURSES);

			if (id == 2)
				return std::make_pair(true, eGraphicsType::LIBMEDIA_SDL2);

			if (id == 3)
				return std::make_pair(true, eGraphicsType::LIBMEDIA_OPENGL);

			return std::make_pair(false, eGraphicsType::LIBMEDIA_NCURSES);	// Garbage
		}

		void _log_from_lib(void) {
			const char * line;

			while ((line = _libMediaInstance->libmedia_getlog()) != nullptr) {
				Logger::log(eLogType::Libmedia, std::string(line));
			}
		}

		void _close(void) {
			_log_from_lib();
			_libMediaInstance->libmedia_end();
			delete _libMediaInstance;
			_libMediaInstance = nullptr;

			LOG(eLogType::Info, "Dlclosing");
			if (dlclose(_dl_image) < 0)
				throw (GraphicsLoaderException(dlerror()));

			_dl_image = nullptr;
			_getLib	  = nullptr;
			delete _current_type;
			_current_type = nullptr;

			LOG(eLogType::Info, "Dlclose success");
		}

		const char * _get_string_of_graphics_current_type(eGraphicsType type) {
			switch (type) {
				case eGraphicsType::LIBMEDIA_SDL2:
					return ("libmedia_sdl2.so");

				case eGraphicsType::LIBMEDIA_NCURSES:
					return ("libmedia_ncurses.so");

				case eGraphicsType::LIBMEDIA_OPENGL:
					return ("libmedia_opengl.so");
			}
		}

		void _open(eGraphicsType type) {
			std::string dlname = BASEPATH;

			dlname += "/";

			_current_type  = new eGraphicsType;
			*_current_type = type;
			dlname		  += _get_string_of_graphics_current_type(type);

			LOG(eLogType::Info, "dlopening", dlname);
			// load the dynamic library
			if ((_dl_image = dlopen(dlname.c_str(), RTLD_LAZY)) == nullptr)
				throw (GraphicsLoaderException(dlerror()));
			// load the getLib func from the dynamic library
			{
				// union because cpplint doesn't allow reinterpret_cast
				union {
					void * void_ptr = nullptr;
					decltype(_getLib)func_ptr;
				} tmp;

				if ((tmp.void_ptr = dlsym(_dl_image, "getLib")) == nullptr)
					throw (GraphicsLoaderException(dlerror()));
				_getLib = tmp.func_ptr;
			}

			// get the ILibMedia instance from the dynamic library
			_libMediaInstance = (*_getLib)();
			LOG(eLogType::Info, "dlopen success", dlname);

			_libMediaInstance->libmedia_begin();
			_log_from_lib();
		}	// _open
	}// namespace

	void load(eGraphicsType type) {
		if (_current_type != nullptr && type == *_current_type)
			return;

		if (_current_type != nullptr)
			_close();
		_open(type);
	}

	void end(void) {
		_close();
	}

	void libmedia_drawgame(size_t width, size_t height, t_item * items, size_t nb_items, uint32_t score) {
		if (_current_type == nullptr)
			throw (GraphicsLoaderException("No library has been loaded yet"));
		_libMediaInstance->libmedia_drawgame(width, height, items, nb_items, score);
		_log_from_lib();
	}

	void libmedia_drawmenu(t_menu menu) {
		if (_current_type == nullptr)
			throw (GraphicsLoaderException("No library has been loaded yet"));
		_libMediaInstance->libmedia_drawmenu(menu);
		_log_from_lib();
	}

	t_input libmedia_input(void) {
		t_input	input;

		if (_current_type == nullptr)
			throw (GraphicsLoaderException("No library has been loaded yet"));
		while (true) {
			input = _libMediaInstance->libmedia_input();
			_log_from_lib();
			if (input.type == CRASH) {
				Core::mode = Core::eMode::EXIT;
			}
			else if (input.type == RCHANGE)	{
				auto p = _assoc_rchange(input.u_input_raw.rchange);
				if (p.first == true) {
					load(p.second);
				}
			}
			break;
		}
		return (input);
	}
}// namespace GraphicsLoader
