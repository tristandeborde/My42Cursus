#ifndef INSTRUCTIONMOD_HPP
# define INSTRUCTIONMOD_HPP

# include "Instructions/IInstruction.hpp"

class InstructionMod: public IInstruction {

public:

	InstructionMod(void);
	~InstructionMod(void);

	bool check();
	void run(std::vector<IOperand const *> &pile);

private:

};

#endif
