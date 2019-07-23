#include "InstructionMod.hpp"

InstructionMod::InstructionMod(void): IInstruction(TokenType::mod) {
	return;
}

InstructionMod::~InstructionMod(void) {
	return;
}

bool InstructionMod::check() {
	return true;
}

void InstructionMod::run(std::vector<IOperand const *> &pile) const {
	if (pile.size() < 2)
		throw std::exception();

	IOperand const *op1 = pile.back();
	pile.pop_back();
	IOperand const *op2 = pile.back();
	pile.pop_back();
	if (op2->toString() == "0" || op2->toString() == "0f")
		throw std::exception();
	IOperand const *op3 = (*op1) % (*op2);
	pile.push_back(op3);
	return;
}
