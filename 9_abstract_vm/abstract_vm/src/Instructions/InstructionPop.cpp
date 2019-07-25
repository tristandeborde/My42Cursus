#include "InstructionPop.hpp"

InstructionPop::InstructionPop(void): IInstruction(eTokenType::pop) {
	return;
}

InstructionPop::~InstructionPop(void) {
	return;
}

bool InstructionPop::check() {
	return true;
}

void InstructionPop::run(std::vector<IOperand const *> &pile) const {
	pile.pop_back();
}
