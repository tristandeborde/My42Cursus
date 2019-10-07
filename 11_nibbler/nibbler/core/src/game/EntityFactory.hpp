#ifndef ENTITYFACTORY_HPP
#define	ENTITYFACTORY_HPP

#include <ostream>

#include "Entity.class.hpp"

class RuleSet;
enum class C_Object;

namespace EntityFactory
{
	enum eEntityType{
		Player = 0,
		Bomb,
		Wall,	// indestructible
		DestructibleWall,
		Fruit,
		Explosion,
		Spawner,
		MenuTimer,
		Body,
		COUNT
	};

	std::ostream &operator<<(std::ostream &os, eEntityType type);

	// Entity construction functions
	Entity * entity(eEntityType type, const Vector2f &pos, const Vector2f &size = Vector2f(1.f, 1.f));
	void linkElemToBody(Entity * elem, ComponentHasBody * body);

	// We need a RuleSet instance for the entity generation
	void setRules(const RuleSet * ruleset);

	// helper funcs
	eEntityType		C_ObjectToEntityType(const C_Object & obj);
}// namespace EntityFactory

#endif	// ENTITYFACTORY_HPP
