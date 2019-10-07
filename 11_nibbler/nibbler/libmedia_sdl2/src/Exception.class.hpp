#ifndef EXCEPTION_CLASS_HPP
#define	EXCEPTION_CLASS_HPP

#include <stdexcept>
#include <string>

class Exception: public std::exception {
	public:
		Exception() = default;
		explicit Exception(const std::string &);
		~Exception() override = default;
		Exception(const Exception &) noexcept;

		Exception &operator=(const Exception &) = default;

		void	setMsg(const std::string &);

		const std::string &	getMsg(void) const;

		const char * what() const noexcept override;
	private:
		std::string	_message;
};

#endif	// ifndef EXCEPTION_CLASS_HPP
