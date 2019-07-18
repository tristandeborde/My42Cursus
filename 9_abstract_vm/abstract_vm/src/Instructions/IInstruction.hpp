#ifndef AINSTRUCTION_HPP
# define AINSTRUCTION_HPP

# include <vector>
# include "Operands/Operand.tpp"

class IInstruction {

public:

	virtual ~IInstruction(void) {};

	virtual bool check() = 0;
	virtual void run(std::vector<IOperand const *> &pile) = 0;

private:

};

#endif
