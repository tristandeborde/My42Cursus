#ifndef ICOMPONENT_CLASS_HPP
#define	   ICOMPONENT_CLASS_HPP

enum class eComponentType{
	Player = 0,
	TimerEvent,
	Move,
	Collision,
	Render,
	LifePoint,
	Damage,
	OnDeathEvent,
	HasBody,
	Score,
	COUNT
};

class IComponent
{
	/* Instantiation **************************************************************/
	public:
		virtual~IComponent(void);

	/* Methods ******************************************************************/
	public:
		virtual eComponentType getType(void) const noexcept = 0;
};

// Get type enum of a class at COMPILE time

template <typename T>
struct type_of_class{};

class ComponentPlayer;
class ComponentTimerEvent;
class ComponentMove;
class ComponentCollision;
class ComponentRender;
class ComponentLifePoint;
class ComponentDamage;
class ComponentOnDeathEvent;
class ComponentHasBody;
class ComponentScore;

template <>
struct type_of_class<ComponentPlayer> {
	eComponentType _type = eComponentType::Player;
};

template <>
struct type_of_class<ComponentTimerEvent> {
	eComponentType _type = eComponentType::TimerEvent;
};

template <>
struct type_of_class<ComponentMove> {
	eComponentType _type = eComponentType::Move;
};

template <>
struct type_of_class<ComponentCollision> {
	eComponentType _type = eComponentType::Collision;
};

template <>
struct type_of_class<ComponentRender> {
	eComponentType _type = eComponentType::Render;
};

template <>
struct type_of_class<ComponentLifePoint> {
	eComponentType _type = eComponentType::LifePoint;
};

template <>
struct type_of_class<ComponentDamage> {
	eComponentType _type = eComponentType::Damage;
};

template <>
struct type_of_class<ComponentOnDeathEvent> {
	eComponentType _type = eComponentType::OnDeathEvent;
};

template <>
struct type_of_class<ComponentHasBody> {
	eComponentType _type = eComponentType::HasBody;
};

template <>
struct type_of_class<ComponentScore> {
	eComponentType _type = eComponentType::Score;
};


#endif	// ICOMPONENT_CLASS_HPP
