#include "Lexer/Token.hpp"

Token::Token(std::string token, TokenType type, int line_nb):
	p_token(token), p_type(type), p_line_nb(line_nb)
{
	return;
}

Token::Token(const Token &src):
	p_token(src.p_token), p_type(src.p_type), p_line_nb(src.p_line_nb)
{
	// Nothing more than a shallow copy-constructor
	return;
}

Token::~Token(void)
{
	return;
}

TokenType Token::getType(void) const
{
	return (this->p_type);
}

std::string Token::getToken(void) const
{
	return (this->p_token);
}

int 		Token::getLineNb(void) const {
	return (this->p_line_nb);
}
