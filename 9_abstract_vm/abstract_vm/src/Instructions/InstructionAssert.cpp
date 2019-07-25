#include "InstructionAssert.hpp"

InstructionAssert::InstructionAssert(void)
	: IInstruction(eTokenType::assert), p_operand(NULL) {
	return;
}

InstructionAssert::~InstructionAssert(void) {
	return;
}

void InstructionAssert::setOperand(IOperand const *operand) {
	this->p_operand = operand;
}

bool InstructionAssert::check(void) {
	return true;
}

void InstructionAssert::run(std::vector<IOperand const *> &pile) const {
	if (!(this->p_operand->toString() == pile.back()->toString()))
	{
		std::cout << "Argument is not equal to the value on top of stack." << std::endl;
		throw std::exception();
	}
	return;
}
