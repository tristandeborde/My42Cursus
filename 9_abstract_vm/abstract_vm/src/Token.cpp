#include "Token.hpp"

Token::Token(std::string token, Lexer::TokenType id, int line_nb, std::string value)
	: p_token(token), p_id(id), p_line_nb(line_nb), p_value(value)
{
	return;
}

Token::~Token(void)
{
	return;
}
