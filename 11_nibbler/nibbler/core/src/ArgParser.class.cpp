#include <map>
#include <iostream>
#include <utility>

#include "ArgParser.class.hpp"

#include "rules/rule_spec.hpp"

constexpr unsigned int XdimMin = NAMERULE_GET_INT_MIN(P1001);
constexpr unsigned int XdimMax = NAMERULE_GET_INT_MAX(P1001);
constexpr unsigned int YdimMin = NAMERULE_GET_INT_MIN(P1002);
constexpr unsigned int YdimMax = NAMERULE_GET_INT_MAX(P1002);

static void print_usage(int argc, char ** argv) {
	std::cout << "usage: " << (argc > 0 ? argv[0] : "./program" ) << " [X_size Y_size] [Library_flag]" << std::endl;
	std::cout << std::endl;
	std::cout << "size limits: " << XdimMin << "x" << YdimMin << " - " << XdimMax << "x" << YdimMax << std::endl;
	std::cout << "libraries:" << std::endl;
	std::cout << "   -lncurse   based on ncurse" << std::endl;
	std::cout << "   -lsdl      based on sdl2" << std::endl;
	std::cout << "   -lopengl   based on opengl and sdl2" << std::endl;
}

int	ArgParser::parse(int argc, char ** argv) {
	if (argc % 2 == 0 && argv[argc - 1][0] == '-') {
		std::map<std::string, eGraphicsType> libList {
			{"-lncurse", eGraphicsType::LIBMEDIA_NCURSES},
			{"-lsdl", eGraphicsType::LIBMEDIA_SDL2},
			{"-lopengl", eGraphicsType::LIBMEDIA_OPENGL},
		};

		auto elem = libList.find(argv[argc - 1]);

		if (elem == libList.end()) {
			std::cout << "invalid library flag: " << argv[argc - 1] << std::endl;
			print_usage(argc, argv);
			return EXIT_FAILURE;
		}

		this->lib = elem->second;

		argc -= 1;
	}

	if (argc == 1) {
		this->dim = std::make_pair(NAMERULE_GET_INT_VAL(P1001), NAMERULE_GET_INT_VAL(P1002));
		return EXIT_SUCCESS;
	}

	if (argc != 3) {
		std::cout << "invalid number of argument." << std::endl;
		print_usage(argc, argv);
		return EXIT_FAILURE;
	}

	size_t result[2]{0, 0};
	for (int i = 0; i < 2; ++i) {
		try {
			result[i] = std::stoul(argv[i + 1]);
		}
		catch (std::invalid_argument &) {
			std::cout << "no conversion could be performed for argument " << i + 1 << "." << std::endl;
			print_usage(argc, argv);
			return EXIT_FAILURE;
		}
		catch (std::out_of_range &) {
			std::cout << "the converted value (argument " << i + 1 << ") would fall out of the range of the result type"
					  << " or std::strtoul sets errno to ERANGE." << std::endl;
			return EXIT_FAILURE;
		}

		if (result[i] > (i == 0 ? XdimMax : YdimMax) || result[i] < (i == 0 ? XdimMin : YdimMin)) {
			std::cout << "Invalid values." << std::endl;
			print_usage(argc, argv);
			return EXIT_FAILURE;
		}
	}

	this->dim = std::make_pair(result[0], result[1]);
	return EXIT_SUCCESS;
}	// parseArgs
