#include "Token.hpp"

Token::Token(std::string token, TokenType type, int line_nb, std::string value):
	p_token(token), p_type(type), p_line_nb(line_nb), p_value(value)
{
	return;
}

Token::Token(const Token &src):
	p_token(src.p_token), p_type(src.p_type), p_line_nb(src.p_line_nb), p_value(src.p_value)
{
	// Nothing more than an explicit version of the implicit copy-constructor
	return;
}

Token::~Token(void)
{
	return;
}
