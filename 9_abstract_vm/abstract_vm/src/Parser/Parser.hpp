#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <string>
# include <regex>
# include <iostream>
# include "Lexer/Lexer.hpp"
# include "Lexer/Token.hpp"
# include "Lexer/TokenType.hpp"
# include "Exceptions/Exceptions.hpp"
# include "Instructions/IInstruction.hpp"
# include "Instructions/InstructionFactory.hpp"
# include "Operands/OperandFactory.hpp"

// Translates a sequence of Token objects into a sequence of Instructions objects.

class Parser {

public:

	typedef std::vector<Token>::const_iterator t_tokens_it;

	Parser(const Lexer &lexer);
	~Parser(void);
	Parser(void) = delete;
	Parser & operator=(const Parser &) = delete;
	Parser(const Parser &) = delete;

	void										printExceptions(const std::vector<std::string> &);
	bool 										isValidNumber(std::string token_str);
	void 										checkToken(t_tokens_it it, t_tokens_it end);
	void 										addInstruction(TokenType type);
	void 										addOperand(t_tokens_it it, TokenType type);
	std::vector<IInstruction const *> const &	getInstructions(void);
	void 										parse(void);

private:
	std::vector<Token>       			p_tokens;
	std::vector<std::string>			p_exceptions;
	std::vector<IInstruction const *> 	p_instructions;
	InstructionFactory 					p_instru_factory;
	OperandFactory 							p_operand_factory;
};

#endif
