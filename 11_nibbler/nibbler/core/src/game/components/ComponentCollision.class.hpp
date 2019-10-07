#ifndef COMPONENTCOLLISION_CLASS_HPP
#define	COMPONENTCOLLISION_CLASS_HPP

#include <functional>

#include "IComponent.class.hpp"
#include "Vector2.class.hpp"

class Party;
class Entity;

class ComponentCollision: public IComponent
{
	public:
		enum class eCollisionType{
			Nothing,
			Eatable,
			DealDamage,
			Block
		};

		// This event is used when eCollisionType is not enough to deduct the behavior
		// For example, what happen when I eat this fruit ?
		/* Typedefs *******************************************************************/
		using t_collision_event = std::function<void(Party & party, Entity * entity)>;

	/* Instantiation **************************************************************/
	public:
		explicit ComponentCollision(eCollisionType _collisionType, t_collision_event event = nullptr);
		~ComponentCollision(void) override;

	/* Attributs ******************************************************************/
	public:
		const eCollisionType collisionType;

		bool hasCollisionEvent(void) const noexcept;
		void execute(Party & party, Entity * entity);

		eComponentType getType(void) const noexcept override;

	private:
		const t_collision_event _event;
		bool _event_is_executed{false};

	/* Compliant methods **********************************************************/
	public:
		ComponentCollision(void) = delete;
		ComponentCollision(const ComponentCollision &) = delete;
		ComponentCollision & operator=(const ComponentCollision &) = delete;
};

using t_collisionType = ComponentCollision::eCollisionType;

#endif	// COMPONENTCOLLISION_CLASS_HPP
