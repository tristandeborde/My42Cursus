#include "Instructions/InstructionExit.hpp"

InstructionExit::InstructionExit(void) {
	return;
}

InstructionExit::~InstructionExit(void) {
	return;
}

bool InstructionExit::check() {
	return true;
}

void InstructionExit::run(std::vector<IOperand const *> &pile) const {
	std::cout << "Exit" << '\n';
	(void)pile;
	return;
}
