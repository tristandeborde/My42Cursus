#include "Exception.class.hpp"

Exception::Exception(const std::string & str) : msg(str) {}

const char	* Exception::what() const noexcept {
	return (this->msg.c_str());
}
