#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <string>
# include <regex>
# include <sstream>
# include <iostream>
# include "TokenType.hpp"
# include "Token.hpp"
# include "Exceptions.hpp"
# include "MapHelper.hpp"

// Separates the input text into a vector of tokens and checks their validity.

class Lexer {

public:

	Lexer(void);
	virtual ~Lexer(void);
	Lexer(const Lexer &) = delete;
	Lexer & operator=(const Lexer &) = delete;

	TokenType					findTokenType(const std::string &identifier);
    Token 						checkToken(const std::string &identifier, int line_nb);
	void						pushToken(const std::string &identifier, int line_nb);
	void						readLine(const std::string &line, int line_nb);
	void 						lex(const std::string &lines);
	std::vector<std::string>	getExceptions(void);
	std::vector<Token::Token>   getTokens(void);

private:

	std::vector<std::pair<std::regex, TokenType>> 	p_valid_tokens;
	std::vector<std::string>						p_exceptions;
    std::vector<Token::Token>           			p_tokens;
};

#endif
