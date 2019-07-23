#ifndef AINSTRUCTION_HPP
# define AINSTRUCTION_HPP

# include <vector>
# include <iostream>
# include "Operands/Operand.tpp"
# include "Lexer/TokenType.hpp"

class IInstruction {

public:

	IInstruction(TokenType);
	virtual ~IInstruction(void) {};

	virtual bool check() = 0;
	virtual void run(std::vector<IOperand const *> &pile) const = 0;

protected:
	TokenType p_type;
};

#endif
