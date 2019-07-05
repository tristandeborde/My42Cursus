#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "Lexer.hpp"

class Token {

public:
	virtual ~Token(void);
	Token(std::string token, Lexer::TokenType id, int line_nb, std::string value);

	Lexer::TokenType getType();

private:
	Token & operator=(const Token &);
	Token(const Token &);
	std::string 		p_token;
	std::string 		p_value;
	Lexer::TokenType 	p_type;
	int 				p_line_nb;

};

#endif
