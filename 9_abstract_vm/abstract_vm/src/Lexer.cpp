#include "Lexer.hpp"

Lexer::Lexer(void) {
	map_init(this->p_authorized_tokens)
		("exit", TokenType::exit)
		("dump", TokenType::dump)
		("push", TokenType::push)
		("pop", TokenType::pop)
		("assert", TokenType::assert)
		("add", TokenType::add)
		("sub", TokenType::sub)
		("mul", TokenType::mul)
		("div", TokenType::div)
		("mod", TokenType::mod)
		("print", TokenType::print)
		("var_int8", TokenType::int8)
		("var_int16", TokenType::int16)
		("var_int32", TokenType::int32)
		("var_float", TokenType::flt)
		("var_double", TokenType::dbl)
	;
	return;
}

Lexer::~Lexer(void) {
	return;
}

void		Lexer::checkTokens()
{
	/*
	 	For token in this->p_tokens:
	 		try checkToken():
				if token->type >= badsyntax;
       		catch LexerException
				cout << e.what() << endl;
	*/
}

TokenType	Lexer::findTokenType(const std::string &token_string)
{
	std::map<std::string, TokenType>::iterator 	found_token;

	found_token = this->p_authorized_tokens.find(token_string);
	if(found_token != this->p_authorized_tokens.end())
		return found_token->second;
	else
		return TokenType::badsyntax;
}

void 	Lexer::handleVar(const std::string &token_string, size_t fst_par, int line_nb)
{
	TokenType		type;
	std::string		value;
	std::string		var_type;
	size_t			snd_par;

	var_type = token_string.substr(0, fst_par - 1);
	type = this->findTokenType(var_type);
	// Check the validity of the variable type
	if (type == TokenType::badsyntax)
	{
		const Token token(token_string, type, line_nb, "");
		this->p_tokens.push_back(token);
	}
	else if ((snd_par = token_string.find(')', fst_par)) == std::string::npos)
	{
		// Check if a second parenthesis is present
		const Token token(token_string, TokenType::missingpar, line_nb, "");
		this->p_tokens.push_back(token);
	}
	else
	{
		// Success: variable type and parenthesis are OK
		value = token_string.substr(fst_par + 1, snd_par - 1);
		const Token token(var_type, type, line_nb, value);
		this->p_tokens.push_back(token);
	}
}

void 	Lexer::handleInstr(const std::string &token_string, int line_nb)
{
	TokenType 		type;

	type = this->findTokenType(token_string);
	// Check if token is an instruction and not a variable type
	if (type > TokenType::print)
		type = TokenType::isolatedvar;
	const Token token(token_string, type, line_nb, "");
	this->p_tokens.push_back(token);
}

void	Lexer::findToken(const std::string &token_string, int line_nb)
{
	size_t			fst_par;

	if ((fst_par = token_string.find('(')))
		this->handleVar(token_string, fst_par, line_nb);
	else
		this->handleInstr(token_string, line_nb);
}

void	Lexer::readLine(const std::string &line, int line_nb)
{
	size_t 	i;
	int 	inst_count;
	int 	start;

	i = 0;
	inst_count = 0;
	// Do not read a comment line
	if (line[i] == ';')
		return;
	// Read every token in a line
	while (i < line.size())
	{
		start = i;
		while (i < line.size() && isalnum(line[i]))
			i++;
		std::string token_string = line.substr(start, i - start);
		this->findToken(token_string, line_nb);
		while (i < line.size() && !isalnum(line[i]))
			i++;
		inst_count++;
	}
}

void Lexer::readLines(const std::string &lines)
{
	std::string 		result;
	std::istringstream 	iss(lines);
	size_t 				line_nb;

	line_nb = 0;
	for (std::string line; std::getline(iss, line); )
	{
	    this->readLine(line, line_nb);
		line_nb++;
	}
}
