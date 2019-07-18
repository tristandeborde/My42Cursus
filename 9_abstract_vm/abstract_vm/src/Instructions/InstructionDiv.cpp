#include "InstructionDiv.hpp"

InstructionDiv::InstructionDiv(void) {
	return;
}

InstructionDiv::~InstructionDiv(void) {
	return;
}

bool InstructionDiv::check() {
	return true;
}

void InstructionDiv::run(std::vector<IOperand const *> &pile) {
	if (pile.size() < 2)
		throw std::exception();

	IOperand const *op1 = pile.back();
	pile.pop_back();
	IOperand const *op2 = pile.back();
	pile.pop_back();

	IOperand const *op3 = (*op1) / (*op2);
	pile.push_back(op3);
	return;
}