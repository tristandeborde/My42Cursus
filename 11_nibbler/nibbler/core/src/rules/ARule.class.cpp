#include "ARule.class.hpp"
#include "atom_rules/BoolRule.class.hpp"
#include "atom_rules/IntRule.class.hpp"

ARule::~ARule() = default;

ARule::ARule(const eRuleName &name, const std::string &short_name)
	: _name(name), _short_name(short_name)
{}

ARule::ARule(const ARule &rhs) : _name(rhs.getName()) {
	*this = rhs;
}

ARule	&ARule::operator=(const ARule &rhs) {
	if (this != &rhs) {
		this->_name		  = rhs.getName();
		this->_short_name = rhs.getShortName();
	}
	return (*this);
}

const eRuleName &ARule::getName() const{
	return (this->_name);
}

const std::string &ARule::getShortName() const{
	return (this->_short_name);
}
