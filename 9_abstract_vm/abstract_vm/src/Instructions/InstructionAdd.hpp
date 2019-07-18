#ifndef INSTRUCTIONADD_HPP
# define INSTRUCTIONADD_HPP

# include "Instructions/IInstruction.hpp"

class InstructionAdd: public IInstruction {

public:

	InstructionAdd(void);
	~InstructionAdd(void);

	bool check();
	void run(std::vector<IOperand const *> &pile);

private:

};

#endif
