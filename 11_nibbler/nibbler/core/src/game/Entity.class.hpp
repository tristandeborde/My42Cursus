#ifndef ENTITY_CLASS_HPP
#define	ENTITY_CLASS_HPP

#include <vector>
#include <cstdint>

#include "Vector2.class.hpp"
#include "game/components/IComponent.class.hpp"


/* Typedefs *******************************************************************/
using t_entity_id = uint32_t;

class Entity final
{
	/* Instantiation **************************************************************/
	public:
		Entity(t_entity_id _id, Vector2f _pos, Vector2f _size = Vector2f(1.f, 1.f));
		~Entity();

	/* Entity methods *************************************************************/
	public:
		void				addComponent(IComponent * component);

		template <typename T>
		T *	getComponent() const{
			const eComponentType searched = type_of_class<T>()._type;

			for (auto * component : this->_components) {
				if (component->getType() == searched) {
					return dynamic_cast<T *>(component);
				}
			}
			return nullptr;
		}

	/* Attributes *****************************************************************/
	private:
		std::vector<IComponent *> _components;

	public:
		const t_entity_id id;
		Vector2f pos;
		Vector2f size;

	/* Coplien methods ************************************************************/
	public:
		Entity() = delete;
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
};

#endif	// ENTITY_CLASS_HPP
