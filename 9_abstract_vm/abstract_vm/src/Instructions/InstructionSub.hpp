#ifndef INSTRUCTIONSUB_HPP
# define INSTRUCTIONSUB_HPP

# include "Instructions/IInstruction.hpp"

class InstructionSub: public IInstruction {

public:

	InstructionSub(void);
	~InstructionSub(void);

	bool check();
	void run(std::vector<IOperand const *> &pile);

private:

};

#endif
