#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "TokenType.hpp"
# include <string>

class Token {

public:
	virtual ~Token(void);
	Token(std::string token, TokenType id, int line_nb, std::string value);
	Token(const Token &);

	TokenType getType();

private:
	Token & operator=(const Token &);
	std::string 	p_token;
	TokenType 		p_type;
	int 			p_line_nb;
	std::string 	p_value;

};

#endif
