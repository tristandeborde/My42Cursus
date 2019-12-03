#include "InstructionAdd.hpp"

InstructionAdd::InstructionAdd(void): IInstruction(eTokenType::add) {
	return;
}

InstructionAdd::~InstructionAdd(void) {
	return;
}

bool InstructionAdd::check() {
	return true;
}

void InstructionAdd::run(std::vector<IOperand const *> &pile) const {
	if (pile.size() < 2)
		throw pileSizeException("Add", 2);

	IOperand const *op1 = pile.back();
	pile.pop_back();
	IOperand const *op2 = pile.back();
	pile.pop_back();

	IOperand const *op3 = (*op1) + (*op2);
	pile.push_back(op3);
	return;
}
