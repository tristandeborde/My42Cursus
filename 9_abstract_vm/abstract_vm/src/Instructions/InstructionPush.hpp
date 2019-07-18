#ifndef INSTRUCTIONPUSH_HPP
# define INSTRUCTIONPUSH_HPP

# include "Instructions/IInstruction.hpp"
# include "Operands/Operand.tpp"

class InstructionPush: public IInstruction {

public:

	InstructionPush();
	~InstructionPush(void);

	bool check();
	void run(std::vector<IOperand const *> &pile);
	void setOperand(IOperand const *);

private:
	IOperand const *p_operand;
};

#endif
