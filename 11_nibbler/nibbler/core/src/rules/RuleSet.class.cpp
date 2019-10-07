#include <sstream>

#include "RuleSet.class.hpp"
#include "rule_factory.hpp"
#include "atom_rules/BoolRule.class.hpp"
#include "atom_rules/IntRule.class.hpp"

#include "exceptions/RuleSetException.class.hpp"

#include "utils/Logger.hpp"

RuleSet::RuleSet() {
	for (size_t i = 0; i < static_cast<size_t>(eRuleName::COUNT); ++i) {
		auto name = static_cast<eRuleName>(i);
		this->_rules.push_back(rule_factory(name));
	}
}

RuleSet::~RuleSet() {
	this->_clear_all_rules();
}

RuleSet::RuleSet(const RuleSet &rhs) {
	*this = rhs;
}

RuleSet	&RuleSet::operator=(const RuleSet &rhs) {
	#define	META_RULE_BOOL(_id, _elem) \
		new BoolRule(*dynamic_cast<BoolRule *>(_elem))

	#define	META_RULE_INT(_id, _elem) \
		new IntRule(*dynamic_cast<IntRule *>(_elem))

	#define	META_RULE_CUSTOM(_id, _elem) \
		new CustomRule<NAMERULE_GET_CUSTOM_TYPE(_id)> \
			(*dynamic_cast<CustomRule<NAMERULE_GET_CUSTOM_TYPE(_id)> *>(_elem))

	#define	META_RULE_LIST(_id, _elem) \
		new ListRule<NAMERULE_GET_LIST_TYPE(_id)> \
			(*dynamic_cast<ListRule<NAMERULE_GET_LIST_TYPE(_id)> *>(_elem))

	#define	META_RULE2(_type) \
		META_RULE_ ## _type

	#define	META_RULE1(_type, _id) \
		META_RULE2(_type)(_id, rhs._rules[static_cast<size_t>(eRuleName::_id)])

	#define	META_RULE(_id) \
		this->_rules.push_back(META_RULE1(NAMERULE_TYPE(_id), _id));

	if (this != &rhs) {
		this->_clear_all_rules();

		FOR_EACH_RULE(META_RULE)
	}

	#undef META_RULE_BOOL
	#undef META_RULE_INT
	#undef META_RULE_CUSTOM
	#undef META_RULE_LIST
	#undef META_RULE2
	#undef META_RULE1
	#undef META_RULE
	return (*this);
}

void RuleSet::logToLogger() const{
	LOG(eLogType::Debug, "RuleSet Dump ( nb rules :", this->_rules.size(), ")");
	for (size_t i = 0; i < static_cast<size_t>(eRuleName::COUNT); ++i) {
		std::stringstream ss;
		std::string	line;

		ss << RuleNameToString(static_cast<eRuleName>(i)) << " <=> ";
		this->_rules[i]->toOstream(ss);
		line = ss.str();
		LOG(eLogType::Debug, line);
	}
}

void RuleSet::_clear_all_rules() {
	for (auto it = this->_rules.begin(); it != this->_rules.end();) {
		delete *it;
		it = this->_rules.erase(it);
	}
}

ARule	* RuleSet::_search_rule(const eRuleName &rule_name) const{
	if (rule_name == eRuleName::COUNT)
		throw RuleSetException(rule_name, eRuleSetExceptionType::NotFound);
	return (this->_rules[static_cast<size_t>(rule_name)]);
}

IntRule	* RuleSet::__getRuleINT(const eRuleName &rule_name) const{
	ARule * rule;

	rule = this->_search_rule(rule_name);
	return (dynamic_cast<IntRule *>(rule));
}

BoolRule * RuleSet::__getRuleBOOL(const eRuleName &rule_name) const{
	ARule * rule;

	rule = this->_search_rule(rule_name);
	return (dynamic_cast<BoolRule *>(rule));
}

int	RuleSet::__getINT(const eRuleName &rule_name) const{
	return (this->__getRuleINT(rule_name)->getInt());
}

bool RuleSet::__getBOOL(const eRuleName &rule_name) const{
	return (this->__getRuleBOOL(rule_name)->val);
}
