#ifndef PARTY_CLASS_HPP
#define	PARTY_CLASS_HPP

#include <unordered_set>
#include <list>

#include "Entity.class.hpp"

#include "rules/RuleSet.class.hpp"

class Party final
{
	/* Typedefs *******************************************************************/
	public:
		using t_dims	   = std::pair<size_t, size_t>;
		using t_entityList = std::list<Entity *>;

	/* Instantiation **************************************************************/
	public:
		Party(void);
		~Party(void);

	/* Party methods ***********************************************************/
	public:
		// getters
		t_dims	getDims(void) const;

		// game-related funcs
		void	initGame(void);
		void	update(void);

		// Entity list methods
		void	addEntity(Entity * entity);
		void	popEntity(Entity * entity);
		void	popEntity(t_entity_id id);

		void	removeAllAndResize(size_t height, size_t width);

		// Deleted Entity list methods
		void	destroyEntity(Entity * entity);
		void	removeDestroyedEntities(void);

		// Temporary getScore() func for Nibbler
		size_t	getScore() const;

	private:
		// Entity list methods
		void	_remove_all_entities(void);

	/* Attributes *****************************************************************/
	public:
		// Entity list
		t_entityList entityList;

		// Rule set
		const RuleSet ruleSet;

	private:

		/*
		 * List of entity to be destroyed.
		 * This list is helpful when we need entities to be destroyed after computation.
		 * we use an unordered_set in order to avoid duplicates.
		 */
		std::unordered_set<Entity *> _deletedEntityList;

		// dimensions of the map
		size_t _height {0};
		size_t _width {0};

	/* Coplien methods ************************************************************/
	public:
		Party  &operator=(Party const &rhs) = delete;
		Party(Party const &src) = delete;
};

#endif	// PARTY_CLASS_HPP
