#include "InstructionMod.hpp"

InstructionMod::InstructionMod(void) {
	return;
}

InstructionMod::~InstructionMod(void) {
	return;
}

bool InstructionMod::check() {
	return true;
}

void InstructionMod::run(std::vector<IOperand const *> &pile) {
	(void)pile;
	return;
}
