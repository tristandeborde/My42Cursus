#ifndef EXCEPTION_CLASS_HPP
#define	EXCEPTION_CLASS_HPP

#include <stdexcept>
#include <string>

class Exception: public std::exception {
	public:
		Exception() = default;
		explicit Exception(const std::string &);
		~Exception() override = default;
		Exception(const Exception &) = default;

		Exception &operator=(const Exception &) = default;

		const char * what() const noexcept override;

	public:
		std::string	msg;
};

#endif	// ifndef EXCEPTION_CLASS_HPP
