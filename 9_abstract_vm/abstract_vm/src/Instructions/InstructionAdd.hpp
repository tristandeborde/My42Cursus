#ifndef INSTRUCTIONADD_HPP
# define INSTRUCTIONADD_HPP

# include "Instructions/IInstruction.hpp"

class InstructionAdd: public IInstruction {

public:

	InstructionAdd(void);
	~InstructionAdd(void);
	InstructionAdd(const InstructionAdd &) = delete;
	InstructionAdd &operator=(const InstructionAdd &) = delete;

	bool check();
	void run(std::vector<IOperand const *> &pile) const;

};

#endif
