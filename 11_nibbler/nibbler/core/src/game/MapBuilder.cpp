#include <random>

#include "MapBuilder.hpp"
#include "EntityFactory.hpp"

#include "rules/rule_spec.hpp"

#include "exceptions/MapBuilderException.class.hpp"

#include "utils/Logger.hpp"

namespace MapBuilder
{
	namespace
	{
		// random engine for random position generation
		std::default_random_engine * _randEng;
		Party::t_dims * _mapSize;
		bool _isInit = false;

		Vector2f	gen_pos(const Party::t_dims &dims) {
			// randX and randY generate random position in a [2, Max - 2] range
			// to avoid spawning near the walls.
			std::uniform_int_distribution<size_t> randX(2, dims.first - 2);
			std::uniform_int_distribution<size_t> randY(2, dims.second - 2);

			return (Vector2f(static_cast<float>(randX(*_randEng)), static_cast<float>(randY(*_randEng))));
		}

		size_t _number_of_freq(const C_Freq & freq) {
			switch (freq) {
				case C_Freq::VeryRare:
					return (1);

				case C_Freq::Rare:
					return (3);

				case C_Freq::Normal:
					return (5);

				case C_Freq::Frequent:
					return (10);

				case C_Freq::VeryFrequent:
					return (20);

				case C_Freq::OneByOne:	// not handled here
					return (0);
			}
		}

		Vector2f get_middle_pos(void) {
			return {_mapSize->first / 2.f - 1.f, _mapSize->second / 2.f};
		}
	}// namespace

	void	init(void) {
		_mapSize = new std::pair<size_t, size_t>(NAMERULE_GET_INT_VAL(P1001), NAMERULE_GET_INT_VAL(P1002));
		_randEng = new std::default_random_engine(static_cast<unsigned int>(time(nullptr)));

		_isInit = true;
	}

	void	end(void) {
		delete _randEng;

		delete _mapSize;

		_isInit = false;
	}

	void	setMapSize(Party::t_dims dims) {
		*_mapSize = dims;
	}

	void	build(Party &party) {
		if (!_isInit)
			throw MapBuilderException("MapBuilder has not been initialized.");

		party.removeAllAndResize(_mapSize->second, _mapSize->first);
		LOG(eLogType::Info, "Generating new map of size (", _mapSize->first, ", ", _mapSize->second, ")");

		if (party.ruleSet.getVal(P1005)) {	// P1005: surrounding walls
			for (size_t	i = 0; i < _mapSize->second; ++i) {
				party.addEntity(EntityFactory::entity(EntityFactory::Wall, Vector2f(0.f, static_cast<float>(i))));
				party.addEntity(EntityFactory::entity(EntityFactory::Wall,
						Vector2f(static_cast<float>(_mapSize->first - 1), static_cast<float>(i))));
			}

			for (size_t i = 1; i < _mapSize->first - 1; ++i) {
				party.addEntity(EntityFactory::entity(EntityFactory::Wall, Vector2f(static_cast<float>(i), 0.f)));
				party.addEntity(EntityFactory::entity(EntityFactory::Wall,
						Vector2f(static_cast<float>(i), static_cast<float>(_mapSize->second - 1))));
			}
		}

		if (party.ruleSet.getVal(P1006)) {	// P1006: is there DestructibleWall entities at start
			for (size_t i = 0; i < 10; ++i) {
				party.addEntity(EntityFactory::entity(EntityFactory::DestructibleWall, gen_pos(*_mapSize)));
			}
		}

		// Player
		party.addEntity(EntityFactory::entity(EntityFactory::Player, get_middle_pos()));

		// Obj at start
		for (auto & obj : party.ruleSet.getVal(P1021)) {								// P1021: list of objects at start
			for (size_t i = 0; i < _number_of_freq(party.ruleSet.getVal(P1023)); ++i) {	// P1023: frequence of P1021
				party.addEntity(EntityFactory::entity(EntityFactory::C_ObjectToEntityType(obj), gen_pos(*_mapSize)));
			}
		}

		// Obj during game
		if (!party.ruleSet.getVal(P1022).empty()) {					// P1022: list of objects in game
			if (party.ruleSet.getVal(P1024) == C_Freq::OneByOne) {	// respawnable fruit (other type of obj are not implemented)
				for (auto & obj : party.ruleSet.getVal(P1022)) {
					party.addEntity(EntityFactory::entity(EntityFactory::C_ObjectToEntityType(obj),
							gen_pos(*_mapSize)));
				}
			}
			else {
				party.addEntity(EntityFactory::entity(EntityFactory::eEntityType::Spawner, Vector2f(-1.f, -1.f)));
			}
		}
	}	// build
}// namespace MapBuilder
