#include "InstructionMul.hpp"

InstructionMul::InstructionMul(void): IInstruction(eTokenType::mul) {
	return;
}

InstructionMul::~InstructionMul(void) {
	return;
}

bool InstructionMul::check() {
	return true;
}

void InstructionMul::run(std::vector<IOperand const *> &pile) const {
	if (pile.size() < 2)
		throw pileSizeException("Mul", 2);

	IOperand const *op1 = pile.back();
	pile.pop_back();
	IOperand const *op2 = pile.back();
	pile.pop_back();

	IOperand const *op3 = (*op1) * (*op2);
	pile.push_back(op3);
	return;
}
