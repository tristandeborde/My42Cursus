#include "InstructionAssert.hpp"

InstructionAssert::InstructionAssert(void): p_operand(NULL) {
	return;
}

InstructionAssert::~InstructionAssert(void) {
	return;
}

void InstructionAssert::setOperand(IOperand const *) {
	return;
}

bool InstructionAssert::check(void) {
	return true;
}

void InstructionAssert::run(std::vector<IOperand const *> &pile) {
	if (this->p_operand == pile.back())
	{
		std::cout << "Argument is not equal to the value on top of stack." << std::endl;
		throw std::exception();
	}
	return;
}
