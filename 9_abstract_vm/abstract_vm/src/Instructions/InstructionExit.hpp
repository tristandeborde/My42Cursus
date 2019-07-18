#ifndef INSTRUCTIONEXIT_HPP
# define INSTRUCTIONEXIT_HPP

# include "Instructions/IInstruction.hpp"

class InstructionExit: public IInstruction {

public:

	InstructionExit(void);
	~InstructionExit(void);

	bool check();
	void run(std::vector<IOperand const *> &pile) const;

private:

};

#endif
