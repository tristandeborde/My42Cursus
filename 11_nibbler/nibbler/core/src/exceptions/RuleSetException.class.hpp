#ifndef RULESET_EXCEPTION_CLASS_HPP
#define	RULESET_EXCEPTION_CLASS_HPP

#include "Exception.class.hpp"
#include "rules/rule_spec.hpp"

enum class eRuleSetExceptionType{
	NotFound,
	IntWrongBoundsInit,
	IntOufOfBounds
};

class RuleSetException: public Exception {
	public:
		RuleSetException(const eRuleName &, const eRuleSetExceptionType &type);
		~RuleSetException() override;

		RuleSetException() = delete;
		RuleSetException(const RuleSetException &) noexcept;
		RuleSetException &operator=(const RuleSetException &) = default;
};

#endif	// ifndef RULESET_EXCEPTION_CLASS_HPP
