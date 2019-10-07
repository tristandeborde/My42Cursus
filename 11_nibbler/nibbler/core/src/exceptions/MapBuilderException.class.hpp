#ifndef MAPBUILDEREXCEPTION_CLASS_HPP
#define	MAPBUILDEREXCEPTION_CLASS_HPP

#include "Exception.class.hpp"

class MapBuilderException: public Exception {
	public:
		explicit MapBuilderException(const std::string &);
		~MapBuilderException() override;

		MapBuilderException() = delete;
		MapBuilderException(const MapBuilderException &) noexcept;
		MapBuilderException &operator=(const MapBuilderException &) = default;
};

#endif	// MAPBUILDEREXCEPTION_CLASS_HPP
