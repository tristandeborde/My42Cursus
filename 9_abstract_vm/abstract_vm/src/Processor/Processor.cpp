#include "Processor.hpp"

Processor::Processor(void) {
	return;
}

Processor::~Processor(void) {
	return;
}

bool Processor::run(std::vector<IInstruction *> const &instructions) {
	for (auto elem : instructions) {
		try {
			elem->run(this->p_pile);
		}
		catch (AVMException &e) {
			std::cout << e.what();
			return false;
		}
	}
	return true;
}
