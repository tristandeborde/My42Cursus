#include "Processor.hpp"

Processor::Processor(void) {
	return;
}

Processor::~Processor(void) {
	return;
}

void Processor::run(std::vector<IInstruction const *> const &instructions) {
	int i = 1;
	//IOperand const *test = new Operand<int>(4, std::string("4"), eOperandType::Int8, 0);
	for (auto elem : instructions) {
		std::cout << "Size: " << this->p_pile.size() << std::endl;
		std::cout << "Instruction code: " << i++ << '\n';
		// elem->setOperand(test);
		elem->run(this->p_pile);
	}
}
