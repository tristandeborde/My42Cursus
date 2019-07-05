#include "Instruction.hpp"

Instruction::Instruction(void) {
	return;
}

Instruction::Instruction(const Instruction &) {
	*this = src;
	return;
}

Instruction::~Instruction(void) {
	return;
}

Instruction & Instruction::operator=(const Instruction &) {
	return *this;
}

