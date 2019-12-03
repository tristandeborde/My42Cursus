#include "InstructionMod.hpp"

InstructionMod::InstructionMod(void): IInstruction(eTokenType::mod) {
	return;
}

InstructionMod::~InstructionMod(void) {
	return;
}

bool InstructionMod::check() {
	return true;
}

void InstructionMod::run(std::vector<IOperand const *> &pile) const {
	if (pile.size() < 2)
		throw pileSizeException("Mod", 2);

	IOperand const *op1 = pile.back();
	pile.pop_back();
	IOperand const *op2 = pile.back();
	pile.pop_back();
	if (op1->toString() == "0" || op1->toString() == "0.")
		throw nullDenominator();
	IOperand const *op3 = (*op2) % (*op1);
	pile.push_back(op3);
	return;
}
