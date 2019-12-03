#include "InstructionPrint.hpp"

InstructionPrint::InstructionPrint(void): IInstruction(eTokenType::print) {
	return;
}

InstructionPrint::~InstructionPrint(void) {
	return;
}

bool InstructionPrint::check() {
	return true;
}

void InstructionPrint::run(std::vector<IOperand const *> &pile) const {
	if (!pile.size())
		throw pileSizeException("Print", 1);
	IOperand const *top_op = pile.back();

	if (top_op->getType() != eOperandType::Int8)
		throw (printTypeException());
	std::cout << static_cast<char>(std::stof(top_op->toString()));
	return;
}
