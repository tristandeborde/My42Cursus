#include "System.hpp"

#include "utils/GraphicsLoader.hpp"

#include "game/components/ComponentRender.class.hpp"
#include "game/components/ComponentScore.class.hpp"
#include "game/components/ComponentHasBody.class.hpp"
#include "game/Party.class.hpp"

namespace System {
	namespace Render {
		namespace {
			void calculate_snake_sprite(Party & party) {
				for (auto & elem : party.entityList) {
					auto * head = elem->getComponent<ComponentHasBody>();
					if (head != nullptr) {
						head->calculateSprite(elem);
					}
				}
			}
		}	// namespace

		void update(Party & party) {
			size_t nb_items;
			size_t i;
			t_item * items;
			uint32_t score = 0;

			calculate_snake_sprite(party);

			const auto dims = party.getDims();

			nb_items = 0;
			for (auto & elem : party.entityList) {
				if (elem->getComponent<ComponentRender>() != nullptr)
					++nb_items;
			}
			if (nb_items == 0) {
				GraphicsLoader::libmedia_drawgame(dims.first, dims.second, nullptr, 0, 0);
				return;
			}

			items = new t_item[nb_items];

			i = 0;
			for (auto & elem : party.entityList) {
				auto * c_render = elem->getComponent<ComponentRender>();
				auto * c_score	= elem->getComponent<ComponentScore>();
				if (c_score != nullptr)
					score = c_score->value;

				if (c_render != nullptr) {
					auto pos = elem->pos;
					items[i].type = c_render->sprite;
					items[i].x	  = static_cast<size_t>(pos.x);
					items[i].y	  = static_cast<size_t>(pos.y);
					++i;
				}
			}

			GraphicsLoader::libmedia_drawgame(dims.first, dims.second, items, nb_items, score);

			delete[] items;
		}	// update
	}		// namespace Render
}			// namespace System
