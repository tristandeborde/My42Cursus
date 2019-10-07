#ifndef COMPONENTLIFEPOINT_CLASS_HPP
#define	COMPONENTLIFEPOINT_CLASS_HPP

#include "IComponent.class.hpp"

class ComponentLifePoint: public IComponent
{
	/* Instantiation **************************************************************/
	public:
		explicit ComponentLifePoint(unsigned int maxHP);
		~ComponentLifePoint(void) override;

	/* Attributs ******************************************************************/
	private:
		unsigned int _maxHP;
		int _currentHP;

	public:
		int		getCurrentHP(void) const;
		void	addHP(int hp);
		void	subHP(int hp);
		bool	isDead() const;

		eComponentType getType(void) const noexcept override;

	/* Compliant methods **********************************************************/
	public:
		ComponentLifePoint() = delete;
		ComponentLifePoint(const ComponentLifePoint &) = delete;
		ComponentLifePoint & operator=(const ComponentLifePoint &) = delete;
};

#endif	// COMPONENTLIFEPOINT_CLASS_HPP
