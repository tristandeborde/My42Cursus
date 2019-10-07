#ifndef ARGPARSER_CLASS_HPP
#define	ARGPARSER_CLASS_HPP

#include <utility>

#include "utils/GraphicsLoader.hpp"

class ArgParser final
{
	/* Instantiation *************************************************************/
	public:
		ArgParser()	 = default;
		~ArgParser() = default;

		ArgParser & operator=(ArgParser const &src) = delete;
		ArgParser(ArgParser const &src) = delete;

	/* Methods ***************************************************************/
	public:
		int parse(int argc, char ** argv);

	/* Attributes ************************************************************/
	public:
		eGraphicsType lib {eGraphicsType::LIBMEDIA_SDL2};
		std::pair<size_t, size_t> dim {0, 0};
};

#endif	// ifndef ARGPARSER_CLASS_HPP
