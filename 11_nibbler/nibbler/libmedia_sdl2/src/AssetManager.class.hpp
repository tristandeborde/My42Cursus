#ifndef ASSETMANAGER_CLASS_HPP
#define	ASSETMANAGER_CLASS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "libmedia_sdl2.h"

#include <string>
#include <map>

#define	MENU_KEY  "menu"
#define	FRUIT_KEY "fruit"
#define	FONT_KEY  "open-sans-bold"

class AssetManager
{
	private:
		static AssetManager * _inst;

	/* Instantiation **************************************************************/
	public:
		static AssetManager * get(void);

	public:
		int         begin(void);
		void        end(void);

		std::pair<SDL_Texture *, SDL_Rect> getTexture(const char * key) const;
		std::pair<SDL_Texture *, SDL_Rect> getTexture(const std::string &key) const;

		TTF_Font * getFont(const char * key) const;
		TTF_Font * getFont(const std::string &key) const;

	/* Methods ********************************************************************/
	private:
		void load_texture(const char * cpath, const std::string &key);
		void load_font(const char * cpath, const std::string &key);

	/* Attributes *****************************************************************/
	private:
		std::map<std::string, std::pair<SDL_Texture *, SDL_Rect> > _textures {};
		std::map<std::string, TTF_Font *> _fonts {};

	/* Coplien methods ************************************************************/
	public:
		AssetManager(void)	= default;
		~AssetManager(void) = default;
		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
};


#endif	// #ifndef ASSETMANAGER_CLASS_HPP
