#ifndef INSTRUCTIONMUL_HPP
# define INSTRUCTIONMUL_HPP

# include "Instructions/IInstruction.hpp"

class InstructionMul: public IInstruction {

public:

	InstructionMul(void);
	~InstructionMul(void);
	InstructionMul(const InstructionMul &) = delete;
	InstructionMul &operator=(const InstructionMul &) = delete;

	bool check();
	void run(std::vector<IOperand const *> &pile) const;

};

#endif
