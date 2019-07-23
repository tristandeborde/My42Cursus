#include "InstructionDump.hpp"

InstructionDump::InstructionDump(void): IInstruction(TokenType::dump) {
	return;
}

InstructionDump::~InstructionDump(void) {
	return;
}

bool InstructionDump::check(void) {
	return true;
}

void InstructionDump::run(std::vector<IOperand const *> &pile) const {
	for (auto it = pile.begin(); it != pile.end() ; it++)
		std::cout << (*it)->toString() << std::endl;
	return;
}
