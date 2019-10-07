#ifndef ARULE_CLASS_HPP
#define	ARULE_CLASS_HPP

#include <string>
#include <ostream>
#include "rule_spec.hpp"

class ARule
{
	/* Instantiation *********************************************************/
	public:
		ARule() = delete;
		ARule(const eRuleName &name, const std::string &short_name);
		virtual~ARule();

		ARule(const ARule &);
		ARule &operator=(const ARule &);

	/* ARule *****************************************************************/
	public:
		const eRuleName		&getName() const;
		const std::string	&getShortName() const;

	/* Virtual methods *******************************************************/
	public:
		virtual eRuleType	getType() const= 0;
		virtual std::ostream &toOstream(std::ostream &os) const= 0;

	/* Attributes ************************************************************/
	private:
		eRuleName _name;
		std::string	_short_name;
};

#endif	// ifndef ARULE_CLASS_HPP
