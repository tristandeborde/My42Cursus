#ifndef INSTRUCTIONASSERT_HPP
# define INSTRUCTIONASSERT_HPP

# include "Instructions/IInstruction.hpp"
# include <iostream>

class InstructionAssert: public IInstruction {

public:

	InstructionAssert(void);
	~InstructionAssert(void);

	bool check();
	void run(std::vector<IOperand const *> &pile);
	void setOperand(IOperand const *);

private:
	IOperand const * p_operand;

};

#endif
