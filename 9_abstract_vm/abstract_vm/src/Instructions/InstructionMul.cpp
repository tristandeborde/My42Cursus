#include "InstructionMul.hpp"

InstructionMul::InstructionMul(void) {
	return;
}

InstructionMul::~InstructionMul(void) {
	return;
}

bool InstructionMul::check() {
	return true;
}

void InstructionMul::run(std::vector<IOperand const *> &pile) {
	if (pile.size() < 2)
		throw std::exception();

	IOperand const *op1 = pile.back();
	pile.pop_back();
	IOperand const *op2 = pile.back();
	if (*op2 == 0)
		throw std::exception();
	pile.pop_back();

	IOperand const *op3 = (*op1) * (*op2);
	pile.push_back(op3);
	return;
}
