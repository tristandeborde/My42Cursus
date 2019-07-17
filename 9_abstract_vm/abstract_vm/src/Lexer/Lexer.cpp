#include "Lexer.hpp"

Lexer::Lexer(void)
{
	this->p_valid_tokens =  {
		std::make_pair(std::regex("\\n"), TokenType::endl),
		std::make_pair(std::regex("exit"), TokenType::exit),
		std::make_pair(std::regex("dump"), TokenType::dump),
		std::make_pair(std::regex("push"), TokenType::push),
		std::make_pair(std::regex("pop"), TokenType::pop),
		std::make_pair(std::regex("assert"), TokenType::assert),
		std::make_pair(std::regex("add"), TokenType::add),
		std::make_pair(std::regex("sub"), TokenType::sub),
		std::make_pair(std::regex("mul"), TokenType::mul),
		std::make_pair(std::regex("div"), TokenType::div),
		std::make_pair(std::regex("mod"), TokenType::mod),
		std::make_pair(std::regex("print"), TokenType::print),
		std::make_pair(std::regex("int8(.*)"), TokenType::int8),
		std::make_pair(std::regex("int16(.*)"), TokenType::int16),
		std::make_pair(std::regex("int32(.*)"), TokenType::int32),
		std::make_pair(std::regex("float(.*)"), TokenType::flt),
		std::make_pair(std::regex("double(.*)"), TokenType::dbl),
	};
	return;
}

Lexer::~Lexer(void)
{
	return;
}

TokenType	Lexer::findTokenType(const std::string &token_str)
{
	// Token is valid (instruction, parenthesis or number)
	for (auto elem : this->p_valid_tokens)
	{
		if (std::regex_search(token_str, elem.first))
			return elem.second;
	}
	// Token is unrecognized
	return TokenType::badsyntax;
}


Token 	Lexer::checkToken(const std::string &token_str, int line_nb)
{
	TokenType 		type;

	type = this->findTokenType(token_str);

	if (type == TokenType::badsyntax)
		throw (badSyntaxException::badSyntaxException(line_nb));
	return Token(token_str, type, line_nb);
}

void	Lexer::pushToken(const std::string &token_str, int line_nb)
{
	try
	{
		this->p_tokens.push_back((this->checkToken(token_str, line_nb)));
	}
	catch (ParserException &e)
	{
		this->p_exceptions.push_back(e.what());
	}
}

void	Lexer::readLine(const std::string &line, int line_nb)
{
	std::string 		token_str;
	std::string 		word;
    std::stringstream 	ss_line(line);

	// Do not read line if it is a comment
	if (line[0] == ';')
		return;
    while (ss_line >> word)
        this->pushToken(word, line_nb);
	this->pushToken("\n", line_nb);
}

void Lexer::lex(const std::string &lines)
{
	std::istringstream 	iss(lines);
	size_t 				line_nb;

	line_nb = 1;
	for (std::string line; std::getline(iss, line); line_nb++)
		this->readLine(line, line_nb);
}

std::vector<std::string>		Lexer::getExceptions(void) const
{
	return this->p_exceptions;
}

std::vector<Token::Token>       Lexer::getTokens(void) const
{
	return this->p_tokens;
}
