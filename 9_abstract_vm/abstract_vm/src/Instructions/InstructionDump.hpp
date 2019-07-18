#ifndef INSTRUCTIONDUMP_HPP
# define INSTRUCTIONDUMP_HPP

# include "Instructions/IInstruction.hpp"
# include <iostream>

class InstructionDump: public IInstruction {

public:

	InstructionDump(void);
	~InstructionDump(void);

	bool check();
	void run(std::vector<IOperand const *> &pile) const;

private:

};

#endif
