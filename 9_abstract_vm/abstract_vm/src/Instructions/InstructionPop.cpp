#include "InstructionPop.hpp"

InstructionPop::InstructionPop(void) {
	return;
}

InstructionPop::~InstructionPop(void) {
	return;
}

bool InstructionPop::check() {
	return true;
}

void InstructionPop::run(std::vector<IOperand const *> &pile) {
	pile.pop_back();
}
