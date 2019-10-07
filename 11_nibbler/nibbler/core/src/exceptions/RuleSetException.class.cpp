#include "RuleSetException.class.hpp"

RuleSetException::RuleSetException(const eRuleName &rn, const eRuleSetExceptionType &type) {
	std::string	line;

	switch (type) {
		case eRuleSetExceptionType::NotFound:
			line += "The following rule was not found : ";
			break;
		case eRuleSetExceptionType::IntWrongBoundsInit:
			line += "Wrong bounds at init for rule : ";
			break;
		case eRuleSetExceptionType::IntOufOfBounds:
			line += "Value is out of bounds for rule : ";
			break;
	}
	line	 += RuleNameToString(rn);
	this->msg = line;
}

RuleSetException::~RuleSetException() = default;

RuleSetException::RuleSetException(const RuleSetException &src) noexcept
	: Exception::Exception(src) {
	*this = src;
}
