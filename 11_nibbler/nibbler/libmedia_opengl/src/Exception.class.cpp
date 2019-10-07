#include "Exception.class.hpp"

Exception::Exception(const std::string & str) : _message(str) {}

Exception::Exception(const Exception &src) noexcept {
	*this = src;
}

void Exception::setMsg(const std::string &str) {
	this->_message = str;
}

const std::string & Exception::getMsg(void) const{
	return (this->_message);
}

const char	* Exception::what() const noexcept {
	return (this->_message.c_str());
}
