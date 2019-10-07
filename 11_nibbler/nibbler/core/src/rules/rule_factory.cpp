#include "rule_factory.hpp"
#include "atom_rules/BoolRule.class.hpp"
#include "atom_rules/IntRule.class.hpp"
#include "atom_rules/CustomRule.class.hpp"
#include "atom_rules/ListRule.class.hpp"

ARule * rule_factory(const eRuleName &name) {
	#define	META_RULE_BOOL(_id, _name) \
		case eRuleName::_id: \
			return new BoolRule(name, _name, \
			NAMERULE_GET_BOOL(_id));

	#define	META_RULE_INT(_id, _name) \
		case eRuleName::_id: \
			return new IntRule(name, _name, \
			NAMERULE_GET_INT_MIN(_id), \
			NAMERULE_GET_INT_MAX(_id), \
			NAMERULE_GET_INT_VAL(_id));

	#define	META_RULE_CUSTOM(_id, _name) \
		case eRuleName::_id: \
			return new CustomRule<NAMERULE_GET_CUSTOM_TYPE(_id)> \
					   (name, _name, NAMERULE_GET_CUSTOM_DEF(_id));

	#define	META_RULE_LIST(_id, _name) \
		case eRuleName::_id: \
			return new ListRule<NAMERULE_GET_LIST_TYPE(_id)> \
					   (name, _name, NAMERULE_GET_LIST_DEF(_id));

	#define	META_RULE2(_type) \
		META_RULE_ ## _type

	#define	META_RULE1(_type, _id, _name) \
		META_RULE2(_type)(_id, _name)

	#define	META_RULE(_id) \
		META_RULE1(NAMERULE_TYPE(_id), _id, NAMERULE_NAME(_id))

	switch (name) {
		FOR_EACH_RULE(META_RULE)
		case eRuleName::COUNT:
			return (nullptr);
	}

	#undef META_RULE
	#undef META_RULE1
	#undef META_RULE2
	#undef META_RULE_BOOL
	#undef META_RULE_INT
	#undef META_RULE_CUSTOM
	#undef META_RULE_LIST
}	// rule_factory
