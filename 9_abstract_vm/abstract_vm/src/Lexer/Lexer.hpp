#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <string>
# include <regex>
# include <sstream>
# include <iostream>
# include "Lexer/TokenType.hpp"
# include "Lexer/Token.hpp"
# include "Exceptions/Exceptions.hpp"

// Converts the input text into a vector of Token objects if they are valid.

class Lexer {

public:

	Lexer(void);
	~Lexer(void);
	Lexer(const Lexer &) = delete;
	Lexer & operator=(const Lexer &) = delete;

	TokenType				findTokenType(const std::string &identifier);
  Token 					checkToken(const std::string &identifier, int line_nb);
	void						pushToken(const std::string &identifier, int line_nb);
	void						readLine(const std::string &line, int line_nb);
	void 						lex(const std::string &lines);
	std::vector<std::string>	getExceptions(void) const;
	std::vector<Token> getTokens(void) const;

private:

	std::vector<std::pair<std::regex, TokenType>> 	p_valid_tokens;
	std::vector<std::string>						p_exceptions;
  std::vector<Token>           				p_tokens;
};

#endif
