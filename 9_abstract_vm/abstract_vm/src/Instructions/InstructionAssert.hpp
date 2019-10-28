#ifndef INSTRUCTIONASSERT_HPP
# define INSTRUCTIONASSERT_HPP

# include "Instructions/IInstruction.hpp"
# include <iostream>

class InstructionAssert: public IInstruction {

public:

	InstructionAssert(void);
	~InstructionAssert(void);
	InstructionAssert(const InstructionAssert &) = delete;
	InstructionAssert &operator=(const InstructionAssert &) = delete;

	bool check();
	void run(std::vector<IOperand const *> &pile) const;
	void setOperand(IOperand const *);

private:
	IOperand const * p_operand;

};

#endif
