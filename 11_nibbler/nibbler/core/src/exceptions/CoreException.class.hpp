#ifndef COREEXCEPTION_CLASS_HPP
#define	COREEXCEPTION_CLASS_HPP

#include "Exception.class.hpp"

class CoreException: public Exception {
	public:
		explicit CoreException(const std::string &);
		~CoreException() override;

		CoreException() = delete;
		CoreException(const CoreException &) noexcept;
		CoreException &operator=(const CoreException &) = default;
};

#endif	// COREEXCEPTION_CLASS_HPP
