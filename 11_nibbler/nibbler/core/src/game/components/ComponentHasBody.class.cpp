#include "ComponentHasBody.class.hpp"
#include "ComponentMove.class.hpp"
#include "ComponentRender.class.hpp"

#include "game/EntityFactory.hpp"
#include "game/Party.class.hpp"

#include "utils/Logger.hpp"

/* Instantiation **************************************************************/

ComponentHasBody::ComponentHasBody(void) {
	// Nibbler ask us to set the default size to 4
	for (int i = 0; i < 3; ++i) {
		this->addBody();
	}
};

ComponentHasBody::~ComponentHasBody(void) {
	if (!this->_newBodyList.empty()) {
		this->_newBodyList.remove_if([](Entity * entity) {
			delete entity;
			return true;
		});
	}
}

/* Attributs ******************************************************************/

eComponentType ComponentHasBody::getType(void) const noexcept {
	return eComponentType::HasBody;
}

void ComponentHasBody::moveBody(Entity * head, Party & party) {
	// head MUST move AFTER the call of this function

	if (this->_newBodyList.empty()) {	// no new body
		if (this->entityList.empty())
			return;

		auto rit = this->entityList.rbegin();
		while (rit != this->entityList.rend()) {
			Entity * current = *rit++;
			Entity * next;
			if (rit == this->entityList.rend())
				next = head;
			else
				next = *rit;
			current->pos = next->pos;
		}
	}
	else {	// new body, we insert it behind the head
		party.addEntity(this->_newBodyList.front());
		this->entityList.push_front(this->_newBodyList.front());
		this->entityList.front()->pos = head->pos;
		this->_newBodyList.pop_front();
	}
}

void ComponentHasBody::addBody(void) {
	// NB: For the moment, a Body entity has no properties that can change in game.
	// when it will, we should create a Entity::Copy() method.
	Entity * new_body = EntityFactory::entity(EntityFactory::eEntityType::Body, Vector2f());

	EntityFactory::linkElemToBody(new_body, this);

	this->_newBodyList.push_back(new_body);
}

void ComponentHasBody::calculateSprite(Entity * head) {
	std::list<Entity *>	snake_lst = this->entityList;// copy

	// add the head ; we will handle it in the for loop
	snake_lst.push_front(head);

	Entity * current = nullptr;
	Entity * prev	 = nullptr;
	Entity * next	 = snake_lst.front();

	for (auto it = snake_lst.begin(); it != snake_lst.end(); prev = current) {	// loop on all the body
		int sprite = 0x0;
		current = next;
		if (it != snake_lst.end()) {
			next = *++it;
		}
		auto * render_c = current->getComponent<ComponentRender>();
		if (render_c == nullptr) {
			LOG(eLogType::Error, "ComponentHasBody::calculateSprite(): Body elem with no ComponentRender");
			continue;
		}

		// special check for end of game: on explosion, we explode all the body
		if (prev != nullptr && prev->getComponent<ComponentRender>()->sprite == t_case::EXPLOSION) {
			render_c->sprite = t_case::EXPLOSION;
			continue;
		}

		// set which type of body sprite we will use
		if (current != snake_lst.front())	// not the head
			sprite |= 1 << 7;
		if (current != snake_lst.back() || snake_lst.size() == 1)	// not the tail, or if their is only 1 entity
			sprite |= 1 << 6;

		// prepare the pos_* vectors
		auto pos_curr = Vector2<int>(current->pos);
		Vector2<int> pos_next(-1, -1);
		Vector2<int> pos_prev(-1, -1);

		if (current != snake_lst.front()) {
			pos_prev = Vector2<int>(prev->pos);
		}

		if (current != snake_lst.back() && snake_lst.size() > 1) {
			pos_next = Vector2<int>(next->pos);
		}
		else if (current == snake_lst.front()) {// only one entity, we will use ComponentMove->direction
			auto * move_c = current->getComponent<ComponentMove>();
			if (move_c == nullptr) {
				LOG(eLogType::Error, "ComponentHasBody::calculateSprite(): Head with no ComponentMove");
				continue;
			}
			pos_next = pos_curr - Vector2<int>(move_c->direction);
		}

		// Compute the sprite direction
		if (pos_prev != -1) {	// can't use operator!=(Vector2<int> v) because travis compiler is dumb
			sprite |= static_cast<int>(pos_curr.x > pos_prev.x)
			  | (static_cast<int>(pos_curr.y < pos_prev.y) << 1)
			  | (static_cast<int>(pos_curr.x < pos_prev.x) << 2)
			  | (static_cast<int>(pos_curr.y > pos_prev.y) << 3);
		}
		if (pos_next != -1) {
			sprite |= static_cast<int>(pos_curr.x > pos_next.x)
			  | (static_cast<int>(pos_curr.y < pos_next.y) << 1)
			  | (static_cast<int>(pos_curr.x < pos_next.x) << 2)
			  | (static_cast<int>(pos_curr.y > pos_next.y) << 3);
		}

		if ((sprite & 0xF) == 0x0) {// no bit are set if their is collision (because the 2 entities will overlap)
			sprite = t_case::EXPLOSION;	// Collision: let's explode the snake
		}

		// set the sprite
		render_c->sprite = static_cast<t_case>(sprite);
	}
}	// ComponentHasBody::calculateSprite
