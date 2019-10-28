#ifndef INSTRUCTIONDIV_HPP
# define INSTRUCTIONDIV_HPP

# include "Instructions/IInstruction.hpp"

class InstructionDiv: public IInstruction {

public:

	InstructionDiv(void);
	~InstructionDiv(void);
	InstructionDiv(const InstructionDiv &) = delete;
	InstructionDiv &operator=(const InstructionDiv &) = delete;

	bool check();
	void run(std::vector<IOperand const *> &pile) const;

};

#endif
