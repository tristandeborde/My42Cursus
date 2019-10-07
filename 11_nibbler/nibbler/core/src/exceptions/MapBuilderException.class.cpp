#include "MapBuilderException.class.hpp"

MapBuilderException::MapBuilderException(const std::string &str)
	: Exception::Exception("MapBuilder Exception : " + str)
{}

MapBuilderException::~MapBuilderException() = default;

MapBuilderException::MapBuilderException(const MapBuilderException &src) noexcept
	: Exception::Exception(src) {
	*this = src;
}
