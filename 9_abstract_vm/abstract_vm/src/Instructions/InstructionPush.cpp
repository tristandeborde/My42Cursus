#include "Instructions/InstructionPush.hpp"

InstructionPush::InstructionPush(void): p_operand(NULL) {
	return;
}

InstructionPush::~InstructionPush(void) {
	return;

}

void InstructionPush::setOperand(IOperand const *operand) {
	this->p_operand = operand;
}

bool InstructionPush::check() {
	return true;
}

void InstructionPush::run(std::vector<IOperand const *> &pile) {
	pile.push_back(this->p_operand);
}
