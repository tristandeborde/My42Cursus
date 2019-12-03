#include "InstructionAssert.hpp"

InstructionAssert::InstructionAssert(void)
	: IInstruction(eTokenType::assert), p_operand(NULL) {
	return;
}

InstructionAssert::~InstructionAssert(void) {
	delete this->p_operand;
	return;
}

void InstructionAssert::setOperand(IOperand const *operand) {
	this->p_operand = operand;
}

bool InstructionAssert::check(void) {
	return true;
}

void InstructionAssert::run(std::vector<IOperand const *> &pile) const {
	double nb_lhs = std::stod(this->p_operand->toString());
	if (!pile.size())
		throw pileEmptyException("Assert");
	double nb_rhs = std::stod(pile.back()->toString());

	if (nb_lhs != nb_rhs || (this->p_operand->getType() != pile.back()->getType()))
		throw assertException();
	return;
}
