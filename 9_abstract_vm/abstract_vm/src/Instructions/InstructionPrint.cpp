#include "InstructionPrint.hpp"

InstructionPrint::InstructionPrint(void): IInstruction(TokenType::print) {
	return;
}

InstructionPrint::~InstructionPrint(void) {
	return;
}

bool InstructionPrint::check() {
	return true;
}

void InstructionPrint::run(std::vector<IOperand const *> &pile) const {
	IOperand const *top_op = pile.back();

	if (top_op->getType() != eOperandType::Int8)
	{
		std::cout << "Argument is not an 8 bit integer." << std::endl;
		throw std::exception();
	}
	std::cout << static_cast<char>(std::stof(top_op->toString())) << std::endl;
	return;
}
