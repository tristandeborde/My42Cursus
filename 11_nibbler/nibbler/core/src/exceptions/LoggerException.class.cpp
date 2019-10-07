#include "LoggerException.class.hpp"

LoggerException::LoggerException(const std::string &str)
	: Exception::Exception("Logger Exception : " + str)
{}

LoggerException::~LoggerException() = default;

LoggerException::LoggerException(const LoggerException &src) noexcept
	: Exception::Exception(src) {
	*this = src;
}
