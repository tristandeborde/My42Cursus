#include "GraphicsLoaderException.class.hpp"

GraphicsLoaderException::GraphicsLoaderException(const std::string &str)
	: Exception::Exception("Graphics Loader Exception : " + str)
{}

GraphicsLoaderException::~GraphicsLoaderException() = default;

GraphicsLoaderException::GraphicsLoaderException(const GraphicsLoaderException &src) noexcept
	: Exception::Exception(src) {
	*this = src;
}
