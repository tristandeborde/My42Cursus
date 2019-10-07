#ifndef BOOLRULE_CLASS_HPP
#define	BOOLRULE_CLASS_HPP

#include "rules/ARule.class.hpp"

class BoolRule: public ARule {
	/* Instantiation *********************************************************/
	public:
		BoolRule() = delete;
		BoolRule(const eRuleName &name, const std::string &short_name, bool _val);
		~BoolRule() override;

		BoolRule(const BoolRule &);
		BoolRule &operator=(const BoolRule &);

	/* Overriden methods *****************************************************/
	public:
		eRuleType	getType() const override;
		std::ostream &toOstream(std::ostream &os) const override;

	/* Attributes ************************************************************/
	public:
		bool val{};
};

#endif	// ifndef BOOLRULE_CLASS_HPP
