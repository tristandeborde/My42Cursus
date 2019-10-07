#include <utility>
#include <iostream>
#include <string>

#include "MainMonad.class.hpp"
#include "ArgParser.class.hpp"
#include "Core.hpp"

#include "rules/rule_spec.hpp"

#include "utils/Logger.hpp"
#include "utils/GraphicsLoader.hpp"

#include "game/MapBuilder.hpp"

int		main(int argc, char ** argv) {
	MainMonad main_monad;
	ArgParser args;

	if (args.parse(argc, argv) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	// Logger
	main_monad.add(Logger::init, Logger::end);
	// MapBuilder
	main_monad.add(MapBuilder::init, MapBuilder::end);
	// This one will not fail, but has to be execute at this moment
	main_monad.add(std::bind(MapBuilder::setMapSize, args.dim), []() {});
	// Core
	main_monad.add(Core::init, Core::end);
	// Graphics Loader
	main_monad.add(std::bind(GraphicsLoader::load, args.lib), GraphicsLoader::end);
	return (main_monad.run(Core::start));
}
