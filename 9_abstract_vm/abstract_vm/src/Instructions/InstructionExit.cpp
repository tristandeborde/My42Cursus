#include "Instructions/InstructionExit.hpp"

InstructionExit::InstructionExit(void): IInstruction(eTokenType::exit) {
	return;
}

InstructionExit::~InstructionExit(void) {
	return;
}

bool InstructionExit::check() {
	return true;
}

void InstructionExit::run(std::vector<IOperand const *> &pile) const {
	(void)pile;
	return;
}
