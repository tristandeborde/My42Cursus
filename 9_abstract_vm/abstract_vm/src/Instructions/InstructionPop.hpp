#ifndef INSTRUCTIONPOP_HPP
# define INSTRUCTIONPOP_HPP

# include "Instructions/IInstruction.hpp"

class InstructionPop: public IInstruction {

public:

	InstructionPop(void);
	~InstructionPop(void);
	InstructionPop(const InstructionPop &) = delete;
	InstructionPop &operator=(const InstructionPop &) = delete;

	bool check();
	void run(std::vector<IOperand const *> &pile) const;

private:
};

#endif
