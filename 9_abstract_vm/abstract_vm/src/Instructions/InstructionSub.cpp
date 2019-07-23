#include "InstructionSub.hpp"

InstructionSub::InstructionSub(void): IInstruction(TokenType::sub) {
	return;
}

InstructionSub::~InstructionSub(void) {
	return;
}

bool InstructionSub::check() {
	return true;
}

void InstructionSub::run(std::vector<IOperand const *> &pile) const {
	if (pile.size() < 2)
		throw std::exception();

	IOperand const *op1 = pile.back();
	pile.pop_back();
	IOperand const *op2 = pile.back();
	pile.pop_back();

	IOperand const *op3 = (*op1) - (*op2);
	pile.push_back(op3);
	return;
}
