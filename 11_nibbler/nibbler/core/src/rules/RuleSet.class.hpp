#ifndef RULESET_CLASS_HPP
#define	RULESET_CLASS_HPP

#include <list>
#include <ostream>
#include <vector>

#include "ARule.class.hpp"
#include "atom_rules/CustomRule.class.hpp"
#include "atom_rules/ListRule.class.hpp"
#include "atom_rules/IntRule.class.hpp"
#include "atom_rules/BoolRule.class.hpp"

#include "utils/preprocessor.hpp"

class RuleSet{
	/* Instantiation *********************************************************/
	public:
		RuleSet();
		virtual~RuleSet();

		RuleSet(const RuleSet &);
		RuleSet &operator=(const RuleSet &);

	/* Methods ***************************************************************/
	public:
		void	logToLogger() const;

	/* Hidden Public Methods *************************************************/

	/**
	 *	This methods must stay public because we use them in getVal and
	 *	getRule macros
	 *	Use RuleSet with getVal and getRule macro thas is defined later in this header
	 */
	public:
		IntRule	* __getRuleINT(const eRuleName &rule_name) const;
		BoolRule * __getRuleBOOL(const eRuleName &rule_name) const;

		template <typename T>
		CustomRule<T> * __getRuleCUSTOM(const eRuleName &rule_name) const{
			ARule * rule;

			rule = this->_search_rule(rule_name);
			return (dynamic_cast<CustomRule<T> *>(rule));
		}

		template <typename T>
		ListRule<T> * __getRuleLIST(const eRuleName &rule_name) const{
			ARule * rule;

			rule = this->_search_rule(rule_name);
			return (dynamic_cast<ListRule<T> *>(rule));
		}

		int				__getINT(const eRuleName &rule_name) const;
		bool			__getBOOL(const eRuleName &rule_name) const;

		template <typename T>
		T				__getCUSTOM(const eRuleName &rule_name) const{
			return (this->__getRuleCUSTOM<T>(rule_name)->getCustom());
		}

		template <typename T>
		typename ListRule<T>::ContainerType	&__getLIST(const eRuleName &rule_name) const{
			return (this->__getRuleLIST<T>(rule_name)->list);
		}

	/* Attributes ************************************************************/
	private:
		std::vector<ARule *> _rules {};

	/* Methods ***************************************************************/
	private:
		ARule * _search_rule(const eRuleName &rule_name) const;
		void	_clear_all_rules();
};

/**
 *	getVal & getRule are hidden macros. It means that from outside we don't see that
 *	they are macros. The purpose of those macros is that, depending of the ruleName,
 *	return type will not be the same.
 *
 *	getVal(Rule_Id): return the value of the rule given as parameter.
 *	getRule(Rule_Id): return a Rule ptr instance corresponding to the rule given as parameter.
 */

#define	_getValINT(_id)		__getINT(eRuleName::_id)
#define	_getValBOOL(_id)	__getBOOL(eRuleName::_id)
#define	_getValCUSTOM(_id)	__getCUSTOM<NAMERULE_GET_CUSTOM_TYPE(_id)>(eRuleName::_id)
#define	_getValLIST(_id)	__getLIST<NAMERULE_GET_LIST_TYPE(_id)>(eRuleName::_id)

#define	getVal(_id)			CONCATENATE(_getVal, NAMERULE_TYPE(_id)) (_id)

#define	_getRuleINT(_id)	__getRuleINT(eRuleName::_id)
#define	_getRuleBOOL(_id)	__getRuleBOOL(eRuleName::_id)
#define	_getRuleCUSTOM(_id) __getRuleCUSTOM<NAMERULE_GET_CUSTOM_TYPE(_id)>(eRuleName::_id)
#define	_getRuleLIST(_id)	__getRuleLIST<NAMERULE_GET_LIST_TYPE(_id)>(eRuleName::_id)

#define	getRule(_id)		CONCATENATE(_getRule, NAMERULE_TYPE(_id)) (_id)

#endif	// ifndef RULESET_CLASS_HPP
