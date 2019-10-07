#include "BoolRule.class.hpp"

BoolRule::~BoolRule() = default;

BoolRule::BoolRule(const eRuleName &name, const std::string &short_name, bool _val)
	: ARule(name, short_name), val(_val)
{}

BoolRule::BoolRule(const BoolRule &rhs) = default;

BoolRule	&BoolRule::operator=(const BoolRule &rhs) = default;

eRuleType BoolRule::getType() const{
	return (eRuleType::Bool);
}

std::ostream	&BoolRule::toOstream(std::ostream &os) const{
	return (os << "BoolRule: " << ((this->val) ? "true" : "false"));
}
