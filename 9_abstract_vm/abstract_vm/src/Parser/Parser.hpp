#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <array>
# include <unordered_map>
# include <string>
# include <regex>
# include <iostream>
# include "Lexer/Lexer.hpp"
# include "Lexer/Token.hpp"
# include "Lexer/eTokenType.hpp"
# include "Exceptions/Exceptions.hpp"
# include "Instructions/IInstruction.hpp"
# include "Instructions/InstructionFactory.hpp"
# include "Operands/OperandFactory.hpp"

// Translates a sequence of Token objects into a sequence of Instructions objects.

class Parser {

public:

	typedef std::vector<Token>::iterator t_tokens_it;

	Parser(const Lexer &lexer);
	~Parser(void);
	Parser(void) = delete;
	Parser & operator=(const Parser &) = delete;
	Parser(const Parser &) = delete;

	void								printExceptions(const std::vector<std::string> &);
	std::string							getNumber(t_tokens_it it);
	void 								lookAhead(t_tokens_it it);
	void 								lookBack(t_tokens_it it);
	void 								addInstruction(eTokenType type);
	void 								addOperand(t_tokens_it it);
	std::vector<IInstruction *> const &	getInstructions(void);
	void 								parse(void);

private:
	std::vector<Token>       							p_tokens;
	std::vector<std::string>							p_exceptions;
	std::vector<IInstruction *> 						p_instructions;
	typedef std::vector<eTokenType> 					t_sequence;
	std::array<t_sequence, static_cast<size_t>(eTokenType::endl)> 		p_ope_seq;
	std::array<eExceptionType, static_cast<size_t>(eTokenType::endl)> 	p_ex_seq;
	InstructionFactory 									p_instru_factory;
	ExceptionFactory 									p_ex_factory;
	OperandFactory 										p_operand_factory;

	void								p_initSeq(void);
	void								p_initExcep(void);
};

#endif
