#ifndef INSTRUCTIONPOP_HPP
# define INSTRUCTIONPOP_HPP

# include "Instructions/IInstruction.hpp"

class InstructionPop: public IInstruction {

public:

	InstructionPop(void);
	~InstructionPop(void);

	bool check();
	void run(std::vector<IOperand const *> &pile);

private:
};

#endif
