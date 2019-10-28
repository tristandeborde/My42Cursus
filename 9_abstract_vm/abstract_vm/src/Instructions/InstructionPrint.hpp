#ifndef INSTRUCTIONPRINT_HPP
# define INSTRUCTIONPRINT_HPP

# include "Instructions/IInstruction.hpp"

class InstructionPrint: public IInstruction {

public:

	InstructionPrint(void);
	~InstructionPrint(void);
	InstructionPrint(const InstructionPrint &) = delete;
	InstructionPrint &operator=(const InstructionPrint &) = delete;

	bool check();
	void run(std::vector<IOperand const *> &pile) const;
};

#endif
