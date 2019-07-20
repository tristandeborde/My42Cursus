#include "InstructionAdd.hpp"

InstructionAdd::InstructionAdd(void) {
	return;
}

InstructionAdd::~InstructionAdd(void) {
	return;
}

bool InstructionAdd::check() {
	return true;
}

void InstructionAdd::run(std::vector<IOperand const *> &pile) const {
	std::cout << "Add" << std::endl;
	if (pile.size() < 2)
		throw std::exception();

	IOperand const *op1 = pile.front();
	pile.pop_back();
	IOperand const *op2 = pile.front();
	pile.pop_back();

	IOperand const *op3 = (*op1) + (*op2);
	pile.push_back(op3);
	return;
}
