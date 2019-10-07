#ifndef CUSTOMRULE_CLASS_HPP
#define	CUSTOMRULE_CLASS_HPP

#include "rules/ARule.class.hpp"

template <typename T>
class CustomRule: public ARule {
	/* Instantiation *********************************************************/
	public:
		CustomRule() = delete;
		CustomRule(const eRuleName &name, const std::string &short_name, const T &val)
			: ARule(name, short_name), _val(val) {}

		~CustomRule() override = default;

		CustomRule(const CustomRule &rhs) = default;
		CustomRule &operator=(const CustomRule &rhs) = default;

	/* Methods ***************************************************************/
	public:
		const T		&getCustom() const{
			return (this->_val);
		}

		void		setCustom(const T &val) {
			this->_val = val;
		}

	/* Overriden methods *****************************************************/
	public:
		eRuleType		getType() const override{
			return (eRuleType::Custom);
		}

		std::ostream	&toOstream(std::ostream &os) const override{
			return (os
				   << "Custom Rule: static_cast<int>(val) = "
				   << static_cast<int>(this->_val));
		}

	/* Attributes ************************************************************/
	private:
		T _val;
};

#endif	// ifndef CUSTOMRULE_CLASS_HPP
