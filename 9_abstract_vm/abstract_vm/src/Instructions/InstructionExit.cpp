#include "Instructions/InstructionExit.hpp"

InstructionExit::InstructionExit(void): IInstruction(TokenType::exit) {
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
