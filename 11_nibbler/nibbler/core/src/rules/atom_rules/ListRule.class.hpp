#ifndef LISTRULE_CLASS_HPP
#define	LISTRULE_CLASS_HPP

#include <vector>
#include "rules/ARule.class.hpp"

template <typename T>
class ListRule: public ARule {
	/* Typedefs *******************************************************************/
	public:
		using ContainerType = std::vector<T>;

	/* Instantiation *********************************************************/
	public:
		ListRule() = delete;
		ListRule(const eRuleName &name, const std::string &short_name, const ContainerType &_list)
			: ARule(name, short_name), list(_list) {}

		~ListRule() override = default;

		ListRule(const ListRule &rhs) = default;
		ListRule &operator=(const ListRule &rhs) = default;

	/* Overriden methods *****************************************************/
	public:
		eRuleType	getType() const override{
			return (eRuleType::List);
		}

		std::ostream	&toOstream(std::ostream &os) const override{
			os << "List Rule: [";
			for (const T & elem : this->list) {
				if (elem != *this->list.cbegin())
					os << " ";
				os << static_cast<int>(elem);
			}
			os << "]";
			return (os);
		}

	/* Attributes ************************************************************/
	public:
		ContainerType list;
};

#endif	// ifndef LISTRULE_CLASS_HPP
