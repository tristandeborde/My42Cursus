#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "Lexer/eTokenType.hpp"
# include "Exceptions/Exceptions.hpp"
# include <string>

class Token {

public:
	virtual ~Token(void);
	Token(std::string token, eTokenType id, int line_nb);
	Token() = delete;
	Token(const Token &);
	Token & operator=(const Token &) = delete;

	eTokenType 	getType(void) const;
	std::string getToken(void) const;
	int 		getLineNb(void) const;

private:
	std::string p_token;
	eTokenType 	p_type;
	int 		p_line_nb;

};

#endif
