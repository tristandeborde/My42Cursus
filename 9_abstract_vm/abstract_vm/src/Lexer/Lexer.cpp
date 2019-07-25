#include "Lexer.hpp"

Lexer::Lexer(void)
{
	this->p_valid_tokens =  {
		std::make_pair(std::regex("\\n"), eTokenType::endl),
		std::make_pair(std::regex("exit"), eTokenType::exit),
		std::make_pair(std::regex("dump"), eTokenType::dump),
		std::make_pair(std::regex("push"), eTokenType::push),
		std::make_pair(std::regex("pop"), eTokenType::pop),
		std::make_pair(std::regex("assert"), eTokenType::assert),
		std::make_pair(std::regex("add"), eTokenType::add),
		std::make_pair(std::regex("sub"), eTokenType::sub),
		std::make_pair(std::regex("mul"), eTokenType::mul),
		std::make_pair(std::regex("div"), eTokenType::div),
		std::make_pair(std::regex("mod"), eTokenType::mod),
		std::make_pair(std::regex("print"), eTokenType::print),
		std::make_pair(std::regex("int8(.*)"), eTokenType::int8),
		std::make_pair(std::regex("int16(.*)"), eTokenType::int16),
		std::make_pair(std::regex("int32(.*)"), eTokenType::int32),
		std::make_pair(std::regex("float(.*)"), eTokenType::flt),
		std::make_pair(std::regex("double(.*)"), eTokenType::dbl),
		std::make_pair(std::regex(";;"), eTokenType::eof),
	};
	return;
}

Lexer::~Lexer(void)
{
	return;
}

eTokenType	Lexer::findeTokenType(const std::string &token_str)
{
	// Token is valid (instruction, parenthesis or number)
	for (auto elem : this->p_valid_tokens)
	{
		if (std::regex_search(token_str, elem.first))
			return elem.second;
	}
	// Token is unrecognized
	return eTokenType::badsyntax;
}


Token 	Lexer::checkToken(const std::string &token_str, int line_nb)
{
	eTokenType 		type;

	type = this->findeTokenType(token_str);

	if (type == eTokenType::badsyntax)
		throw (badSyntaxException(line_nb));
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
	this->pushToken(";;", line_nb);
}

std::vector<std::string>		Lexer::getExceptions(void) const
{
	return this->p_exceptions;
}

std::vector<Token>       Lexer::getTokens(void) const
{
	return this->p_tokens;
}
