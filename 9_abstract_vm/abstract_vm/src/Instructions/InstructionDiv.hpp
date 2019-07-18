#ifndef INSTRUCTIONDIV_HPP
# define INSTRUCTIONDIV_HPP

# include "Instructions/IInstruction.hpp"

class InstructionDiv: public IInstruction {

public:

	InstructionDiv(void);
	~InstructionDiv(void);

	bool check();
	void run(std::vector<IOperand const *> &pile);

private:

};

#endif
