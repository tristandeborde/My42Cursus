#ifndef AINSTRUCTION_HPP
# define AINSTRUCTION_HPP

# include <vector>
# include <iostream>
# include "Operands/Operand.tpp"

class IInstruction {

public:

	virtual ~IInstruction(void) {};

	virtual bool check() = 0;
	virtual void run(std::vector<IOperand const *> &pile) const = 0;

private:

};

#endif
