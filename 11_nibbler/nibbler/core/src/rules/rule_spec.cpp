#include "rule_spec.hpp"

const std::string	RuleNameToString(const eRuleName & rn) {
	#define	CC(_id) \
		case eRuleName::_id: \
			return # _id;

	switch (rn) {
		FOR_EACH_RULE(CC)
		CC(COUNT)
	}
}
