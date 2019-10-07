#include "CoreException.class.hpp"

CoreException::CoreException(const std::string &str)
	: Exception::Exception("Core Exception : " + str)
{}

CoreException::~CoreException() = default;

CoreException::CoreException(const CoreException &src) noexcept
	: Exception::Exception(src) {
	*this = src;
}
