#include "AssetManager.class.hpp"
#include "RendererManager.class.hpp"
#include "Exception.class.hpp"
#include "CSVReader.class.hpp"
#include "Config.hpp"

AssetManager * AssetManager::_inst = nullptr;

AssetManager         * AssetManager::get(void) {
	if (AssetManager::_inst == nullptr) {
		AssetManager::_inst = new AssetManager();
	}
	return AssetManager::_inst;
}

int AssetManager::begin(void) {
	if (TTF_Init() == -1) {
		throw Exception("Error TTF_Init : ");
	}

	this->load_texture(PATH_BOMBERMAN_BMP, PATH_BOMBERMAN_CSV);
	this->load_texture(PATH_SNAKE_BMP, PATH_SNAKE_CSV);
	this->load_texture(PATH_MENU_BMP, MENU_KEY);
	this->load_texture(PATH_FRUIT_BMP, FRUIT_KEY);
	this->load_font(PATH_OPENSB_TTF, FONT_KEY);
	return 0;
}

void AssetManager::end(void) {
	for (auto & elem : this->_textures) {
		SDL_DestroyTexture(elem.second.first);
		elem.second.first = nullptr;
	}
	for (auto & elem : this->_fonts) {
		TTF_CloseFont(elem.second);
		elem.second = nullptr;
	}

	TTF_Quit();
	if (AssetManager::_inst != nullptr) {
		delete AssetManager::_inst;
		AssetManager::_inst = nullptr;
	}
}

std::pair<SDL_Texture *, SDL_Rect> AssetManager::getTexture(const char * key) const{
	auto elem = this->_textures.find(key);

	if (elem == this->_textures.end())
		return {nullptr, SDL_Rect()};

	return elem->second;
}

std::pair<SDL_Texture *, SDL_Rect> AssetManager::getTexture(const std::string &key) const{
	auto elem = this->_textures.find(key);

	if (elem == this->_textures.end())
		return {nullptr, SDL_Rect()};

	return elem->second;
}

TTF_Font * AssetManager::getFont(const char * key) const{
	auto elem = this->_fonts.find(key);

	if (elem == this->_fonts.end())
		return nullptr;

	return elem->second;
}

TTF_Font * AssetManager::getFont(const std::string &key) const{
	auto elem = this->_fonts.find(key);

	if (elem == this->_fonts.end())
		return nullptr;

	return elem->second;
}

static bool is_csv(const std::string &str) {
	if (str.substr(str.size() - 4) == ".csv")
		return true;

	return false;
}

void AssetManager::load_texture(const char * cpath, const std::string &key) {
	SDL_Surface * surface;
	SDL_Texture * texture;
	std::string	path(BASEPATH);

	path += cpath;
	if ((surface = SDL_LoadBMP(path.c_str())) == nullptr) {
		throw Exception("Error SDL_LoadBMP : ");
	}
	if ((texture = SDL_CreateTextureFromSurface(RendererManager::get()->getRenderer(), surface)) == nullptr) {
		SDL_FreeSurface(surface);
		throw Exception("Error SDL_CreateTextureFromSurface : ");
	}

	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	if (is_csv(key) == true) {
		path  = BASEPATH;
		path += key;

		CSVReader csv(path);
		auto data = csv.getData(true);

		int all_x, all_y;
		all_x = std::stoi(data.at(0).at(1)) + 1;
		all_y = std::stoi(data.at(0).at(2)) + 1;

		for (auto &elem : data) {
			if (elem.size() != 4)
				throw Exception("CSV bad size");

			int x, y, size;
			x	 = std::stoi(elem.at(1));
			y	 = std::stoi(elem.at(2));
			size = std::stoi(elem.at(3));

			auto rect = SDL_Rect({(w * x) / all_x, (h * y) / all_y, (w * size) / all_x, (h * size) / all_y});
			this->_textures.insert({elem.at(0), {texture, rect}});
		}
	}
	else {
		this->_textures.insert({key, {texture, SDL_Rect({0, 0, w, h})}});
	}
	SDL_FreeSurface(surface);
}	// AssetManager::load_texture

void AssetManager::load_font(const char * cpath, const std::string &key) {
	std::string	path(BASEPATH);
	TTF_Font * font;

	path += cpath;
	if ((font = TTF_OpenFont(path.c_str(), 65)) == nullptr) {
		throw Exception("Error TTF_OpenFont : ");
	}
	this->_fonts.insert({key, font});
}
