#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "Lexer/TokenType.hpp"
# include "Exceptions/Exceptions.hpp"
# include <string>

class Token {

public:
	virtual ~Token(void);
	Token(std::string token, TokenType id, int line_nb);
	Token(const Token &);
	Token & operator=(const Token &) = delete;

	TokenType 	getType(void) const;
	std::string getToken(void) const;
	int 		getLineNb(void) const;

private:
	std::string p_token;
	TokenType 	p_type;
	int 		p_line_nb;

};

#endif
