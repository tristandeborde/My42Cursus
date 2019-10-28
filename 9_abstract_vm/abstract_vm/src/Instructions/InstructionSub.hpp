#ifndef INSTRUCTIONSUB_HPP
# define INSTRUCTIONSUB_HPP

# include "Instructions/IInstruction.hpp"

class InstructionSub: public IInstruction {

public:

	InstructionSub(void);
	~InstructionSub(void);
	InstructionSub(const InstructionSub &) = delete;
	InstructionSub &operator=(const InstructionSub &) = delete;

	bool check();
	void run(std::vector<IOperand const *> &pile) const;

};

#endif
