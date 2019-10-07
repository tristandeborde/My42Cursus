#ifndef INTRULE_CLASS_HPP
#define	INTRULE_CLASS_HPP

#include "rules/ARule.class.hpp"

class IntRule: public ARule {
	/* Instantiation *********************************************************/
	public:
		IntRule() = delete;
		IntRule(const eRuleName &name, const std::string &short_name, int min, int max, int val);
		~IntRule() override;

		IntRule(const IntRule &);
		IntRule &operator=(const IntRule &);

	/* Methods ***************************************************************/
	public:
		std::pair<int, int>		getBounds() const;
		int						getInt() const;
		void					setInt(int val);

	/* Overriden methods *****************************************************/
	public:
		eRuleType	getType() const override;
		std::ostream &toOstream(std::ostream &os) const override;

	/* Attributes ************************************************************/
	private:
		int	_min{};
		int	_max{};
		int	_val{};
};

#endif	// ifndef INTRULE_CLASS_HPP
