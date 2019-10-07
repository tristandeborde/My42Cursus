#include "IntRule.class.hpp"
#include "exceptions/RuleSetException.class.hpp"

IntRule::~IntRule() = default;

IntRule::IntRule(const eRuleName &name, const std::string &short_name, int min, int max, int val)
	: ARule(name, short_name), _min(min), _max(max), _val(val) {
	if (min > max)
		throw RuleSetException(name, eRuleSetExceptionType::IntWrongBoundsInit);
	if (val < min || val > max)
		throw RuleSetException(name, eRuleSetExceptionType::IntOufOfBounds);
}

IntRule::IntRule(const IntRule &rhs) = default;

IntRule &IntRule::operator=(const IntRule &rhs) = default;

std::pair<int, int>	IntRule::getBounds() const{
	return (std::make_pair(this->_min, this->_max));
}

int IntRule::getInt() const{
	return (this->_val);
}

void IntRule::setInt(int val) {
	if (val < this->_min || val > this->_max)
		throw RuleSetException(this->getName(), eRuleSetExceptionType::IntOufOfBounds);
	this->_val = val;
}

eRuleType IntRule::getType() const{
	return (eRuleType::Integer);
}

std::ostream	&IntRule::toOstream(std::ostream &os) const{
	return (os << "IntRule: " << this->_val);
}
