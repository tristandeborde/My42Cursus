#ifndef LOGGER_EXCEPTION_CLASS_HPP
#define	LOGGER_EXCEPTION_CLASS_HPP

#include "Exception.class.hpp"

class LoggerException: public Exception {
	public:
		explicit LoggerException(const std::string &);
		~LoggerException() override;

		LoggerException() = delete;
		LoggerException(const LoggerException &) noexcept;
		LoggerException &operator=(const LoggerException &) = default;
};

#endif	// ifndef LOGGER_EXCEPTION_CLASS_HPP
