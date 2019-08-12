#include "Processor.hpp"

Processor::Processor(void) {
	return;
}

Processor::~Processor(void) {
	return;
}

void Processor::run(std::vector<IInstruction *> const &instructions) {
	for (auto elem : instructions) {
		elem->run(this->p_pile);
	}
}
