#ifndef INSTRUCTIONDUMP_HPP
# define INSTRUCTIONDUMP_HPP

# include "Instructions/IInstruction.hpp"
# include <iostream>

class InstructionDump: public IInstruction {

public:

	InstructionDump(void);
	~InstructionDump(void);
	InstructionDump(const InstructionDump &) = delete;
	InstructionDump &operator=(const InstructionDump &) = delete;

	bool check();
	void run(std::vector<IOperand const *> &pile) const;
};

#endif
