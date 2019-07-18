#include "Parser/Parser.hpp"

Parser::Parser(const Lexer &src)
	: p_tokens(src.getTokens()), p_exceptions(src.getExceptions()) {
	return;
}

Parser::~Parser(void) {
	return;
}

void	Parser::printExceptions(const std::vector<std::string> &exceptions)
{
	for (auto elem : exceptions)
		std::cout << elem << std::endl;
	throw (GenericException::GenericException());
}

bool 	Parser::isValidNumber(std::string token_str)
{
	if (std::regex_search(token_str, std::regex("\\(\\d*\\.?\\d*\\)")))
		return true;
	return false;
}

void 	Parser::checkToken(t_tokens_it it, t_tokens_it end)
{
	t_tokens_it next = it + 1;
	TokenType type = (*it).getType();

	// TODO: Change ugly if forest into sequence parsing:
	// 		check vector<string s> Tokens against vector<vector<string s>> Valid_Sequences

	// IF INSTR == (Push || Assert) : Look ahead to check if next is number
	if (type == TokenType::push || type == TokenType::assert) {
		if (next == end || (*next).getType() < TokenType::int8)
			throw (missingNumberException::missingNumberException((*it).getLineNb()));
	}
	// IF NB || INSTR != (Push || Assert) : Look ahead to check if \n
	if (type != TokenType::endl && type != TokenType::push && type != TokenType::assert) {
		if (next == end || (*next).getType() != TokenType::endl)
			throw (forbiddenInstructionException::forbiddenInstructionException((*it).getLineNb()));
	}
	// IF NB: check if value is (valid format && !overflow//underflow)
	if (type != TokenType::endl && type >= TokenType::int8) {
		if (!(this->isValidNumber((*it).getToken())))
			throw (invalidNumberException::invalidNumberException((*it).getLineNb()));
	}
	// IF LAST != exit
	if (next->getType() == TokenType::endl && (next + 1) == end && type != TokenType::exit) {
		throw (noExitException::noExitException((*it).getLineNb()));
	}
}

void 	Parser::addInstruction(t_tokens_it it)
{
	// Check if token is an instruction (not an Operand, not an error)
	TokenType type = (*it).getType();
	if (type > TokenType::print)
		return ;

	IInstruction const *instru = this->p_factory.createInstruction(type);
	this->p_instructions.push_back(instru);
}

void 	Parser::parse(void)
{
	for (t_tokens_it it = this->p_tokens.begin(); it != this->p_tokens.end(); it++) {
		try {
			this->checkToken(it, this->p_tokens.end());
			this->addInstruction(it);
		}
		catch (ParserException &e) {
			this->p_exceptions.push_back(e.what());
		}
	}
	if (this->p_exceptions.size())
		this->printExceptions(this->p_exceptions);
}

std::vector<IInstruction const *> const  &Parser::getInstructions(void) {
	return this->p_instructions;
}
