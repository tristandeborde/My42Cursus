#ifndef INSTRUCTIONPUSH_HPP
# define INSTRUCTIONPUSH_HPP

# include "Instructions/IInstruction.hpp"
# include "Operands/Operand.hpp"

class InstructionPush: public IInstruction {

public:

	InstructionPush();
	~InstructionPush(void);
	InstructionPush(const InstructionPush &) = delete;
	InstructionPush &operator=(const InstructionPush &) = delete;

	bool check();
	virtual void run(std::vector<IOperand const *> &pile) const;
	void setOperand(IOperand const *);

private:
	IOperand const *p_operand;
};

#endif
