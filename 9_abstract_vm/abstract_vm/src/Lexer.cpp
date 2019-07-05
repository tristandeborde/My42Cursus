#include "Lexer.hpp"

Lexer::Lexer(void) {
	this->p_authorized_instr["exit"] = exit;
	this->p_authorized_instr["dump"] = dump;
	this->p_authorized_instr["push"] = push;
	this->p_authorized_instr["pop"] = pop;
	this->p_authorized_instr["assert"] = assert;
	this->p_authorized_instr["add"] = add;
	this->p_authorized_instr["sub"] = sub;
	this->p_authorized_instr["mul"] = mul;
	this->p_authorized_instr["div"] = div;
	this->p_authorized_instr["mod"] = mod;
	this->p_authorized_instr["print"] = print;
	this->p_authorized_var["var_int8"] = int8;
	this->p_authorized_var["var_int16"] = int16;
	this->p_authorized_var["var_int32"] = int32;
	this->p_authorized_var["var_float"] = flt;
	this->p_authorized_var["var_double"] = dbl;
	return;
}

Lexer::~Lexer(void) {
	return;
}

const char* Lexer::badSyntaxException::what(int line_nb) const throw()
{
	std::string statement = "Line ";
	statement += std::to_string(line_nb);
	statement += "Syntax error, no match found for expression.";
	return statement;
}

const char* Lexer::missingParenthesisException::what(int line_nb) const throw()
{
	std::string statement = "Line ";
	statement += std::to_string(line_nb);
	statement += "Syntax error, missing parenthesis after value call.";
	return statement;
}

Lexer::TokenType	Lexer::findTokenType(const std::string &identifier, int TokenType)
{
	Token::Token 							*token;
	std::map<std::string, Lexer::TokenType> *map;

	map = TokenType ? &this->p_authorized_instr : &this->p_authorized_var;
	found_token = map.find(identifier);
	if(found_token != map.end())
		return found_token->second;
	else
		return TokenType::error;
}

void 	Lexer::handleVar(const std::string &identifier, size_t fst_par, int line_nb)
{
	TokenType		type;
	std::string		value;
	std::string		token;
	size_t			snd_par;

	token = identifier.substr(0, fst_par - 1);
	type = this->findTokenType(token, 0);
	if ((snd_par = identifier.find(')', fst_par)) != std::string::npos
		&& snd_par == identifier.end() - 1 && type != TokenType::error)
	{
		value = identifier.substr(fst_par + 1, snd_par - 1);
		this->p_tokens.push_back(new Token::Token(token, type, line_nb, value));
	}
	else
	{
		type = TokenType::error;
		this->p_errors.push_back(new Token::Token(identifier, type, line_nb, ""));
	}
}

void	Lexer::findToken(const std::string &identifier, int line_nb)
{
	Token::Token	*token;
	TokenType		type;
	size_t			fst_par;

	if ((fst_par = identifier.find('(')))
		this->handleVar(identifier, fst_par, line_nb);
	else
	{
		type = this->findTokenType(identifier, 1);
		if (type == Type::int8 || type == Type::int16
			|| type == Type::int32 || type == Type::float)
			type = TokenType::error;
		token = new Token::Token(identifier, type, line_nb, "");
		this->p_tokens.push_back(token);
	}
}

void	Lexer::readLine(const std::string &line)
{
	int i;
	int inst_count;
	int start;

	i = 0;
	inst_count = 0;
	if (line[i] == ';')
		return;
	while (i < line.size())
	{
		start = i;
		while (i < line.size() && isalnum(line[i]))
			i++;
		string identifier = line.substr(start, i - start);
		this->findToken(identifier);
		while (i < line.size() && !isalnum(line[i]))
			i++;
		inst_count++;
	}
}
