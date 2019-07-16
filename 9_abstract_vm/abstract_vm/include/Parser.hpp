#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <string>
# include <regex>
# include <iostream>
# include "Lexer.hpp"
# include "Token.hpp"
# include "TokenType.hpp"
# include "Exceptions.hpp"

// Parses a sequence of tokens to check for inconstencies.

class Parser {

public:

	typedef std::vector<Token::Token>::const_iterator t_tokens_it;

	Parser(Lexer &src);
	Parser(void) = delete;
	virtual ~Parser(void);
	Parser & operator=(const Parser &) = delete;
	Parser(const Parser &) = delete;

	bool 	overflowCheck(const std::string &nb);
	void	printExceptions(const std::vector<std::string> &);
	bool 	isValidNumber(std::string token_str);
	void 	checkToken(t_tokens_it it, t_tokens_it end);
	void 	parse(void);

private:
	std::vector<Token::Token>       p_tokens;
	std::vector<std::string>		p_exceptions;
};

#endif
