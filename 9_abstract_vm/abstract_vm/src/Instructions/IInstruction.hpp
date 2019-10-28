#ifndef AINSTRUCTION_HPP
# define AINSTRUCTION_HPP

# include <vector>
# include <iostream>
# include "Operands/Operand.tpp"
# include "Lexer/eTokenType.hpp"

class IInstruction {

public:

	IInstruction(eTokenType);
	virtual ~IInstruction(void) {};
	IInstruction(void) = delete;
	IInstruction(const IInstruction &) = delete;
	const IInstruction & operator=(const IInstruction &) = delete;

	virtual bool check() = 0;
	virtual void run(std::vector<IOperand const *> &pile) const = 0;

protected:
	eTokenType p_type;

};

#endif
