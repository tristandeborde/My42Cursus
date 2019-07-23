#ifndef PROCESSOR_HPP
# define PROCESSOR_HPP

# include "Instructions/IInstruction.hpp"
# include "Operands/IOperand.hpp"

// Takes a sequence of IInstruction objects as input and executes them on a stack.

class Processor {

public:

	Processor(void);
	~Processor(void);
	Processor(const Processor &) = delete;
	Processor & operator=(const Processor &) = delete;

	void 	run(std::vector<IInstruction *> const &instructions);

private:
	std::vector<IOperand const *> p_pile;
};

#endif
