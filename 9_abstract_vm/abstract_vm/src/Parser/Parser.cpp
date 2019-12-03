#include "Parser/Parser.hpp"

Parser::Parser(const Lexer &src)
	: p_tokens(src.getTokens()), p_exceptions(src.getExceptions()) {
	this->p_initSeq();
	return;
}

Parser::~Parser(void) {
	for (auto elem : this->p_instructions) {
		delete elem;
	}
	return;
}

bool	Parser::printExceptions(const std::vector<std::string> &exceptions)
{
	if (!exceptions.size())
		return true;
	for (auto elem : exceptions)
		std::cout << elem;
	return false;
}

std::string 	Parser::getNumber(t_tokens_it it)
{
	std::smatch nb;
	std::string token_str = (*it).getToken();

	if (!std::regex_search(token_str, nb, std::regex("\\(([-]?\\d*\\.?\\d*)\\)"))
		|| !nb[1].str().size())
		throw (invalidNumberException(it->getLineNb(), it->getToken()));

	return nb[1].str();
}

void 	Parser::addOperand(t_tokens_it it)
{
	eTokenType 	type = it->getType();
	std::string nb = this->getNumber(it);

	// Check if token is operand -> attach to prev Instr
	eOperandType type_conv = static_cast<eOperandType>(static_cast<int>(type) - 11);

	// INSTRUCTIONS LIST EMPTY
	auto prev = this->p_instructions.back();
	InstructionPush *push = dynamic_cast<InstructionPush *>(prev);
	if (push != nullptr)
		push->setOperand(this->p_operand_factory.createOperand(type_conv, nb));
	InstructionAssert *assert = dynamic_cast<InstructionAssert *>(prev);
	if (assert != nullptr)
		assert->setOperand(this->p_operand_factory.createOperand(type_conv, nb));
}

void 	Parser::addInstruction(eTokenType type)
{
	// Token is Instruction
	IInstruction *instru = this->p_instru_factory.createInstruction(type);
	this->p_instructions.push_back(instru);
}

void 	Parser::lookBack(t_tokens_it it)
{
	// Only lookback case is for eof token which must be preceded by endl and then exit 
	if ((it != this->p_tokens.begin() && (it - 1)->getType() != eTokenType::endl)
		|| ((it - 1) != this->p_tokens.begin() && (it - 2)->getType() != eTokenType::exit))
	throw (noExitException(it->getLineNb()));
}

void 	Parser::lookAhead(t_tokens_it it)
{
	eTokenType type_it = it->getType();
	t_tokens_it next = it + 1;

	// Check if next token is valid; if not, throw error
	auto valid_tokens = this->p_ope_seq[static_cast<size_t>(type_it)];
	auto found_token = std::find(valid_tokens.begin(), valid_tokens.end(), next->getType());
	if (found_token == valid_tokens.end())
		throw ( this->p_ex_factory.create( this->p_ex_seq[static_cast<size_t>(type_it)], it->getLineNb()) );

	// Token is valid so convert it to Instruction or Operand
	if (type_it <= eTokenType::print)
		this->addInstruction(type_it);
	else if (type_it <= eTokenType::dbl && this->p_instructions.size())
		this->addOperand(it);
}

bool 	Parser::parse(void)
{
	for (t_tokens_it it = this->p_tokens.begin(); it != this->p_tokens.end(); it++) {
		try {
			if (it->getType() != eTokenType::eof)
				this->lookAhead(it);
			else
				this->lookBack(it);
		}
		catch (AVMException &e) {
			this->p_exceptions.push_back(e.what());
		}
	}
	return (this->printExceptions(this->p_exceptions));
}

std::vector<IInstruction *> const  &Parser::getInstructions(void) {
	return this->p_instructions;
}

// Private Methods ***********************************************************

void	Parser::p_initSeq(void) {
	std::vector<eTokenType> all = 
	{
		eTokenType::exit,
		eTokenType::dump,
		eTokenType::push,
		eTokenType::pop,
		eTokenType::assert,
		eTokenType::add,
		eTokenType::sub,
		eTokenType::mul,
		eTokenType::div,
		eTokenType::mod,
		eTokenType::print,
		eTokenType::eof,
		eTokenType::int8,
		eTokenType::int16,
		eTokenType::int32,
		eTokenType::flt,
		eTokenType::dbl,
	};
	std::vector<eTokenType> instr;
	std::copy(all.begin(), all.begin() + 12, std::back_inserter(instr));
	std::vector<eTokenType> ope;
	std::copy(all.begin() + 11, all.end(), std::back_inserter(ope));

	this->p_ope_seq = {{
		{eTokenType::endl}, // exit
		{eTokenType::endl},
		{ope}, // push
		{eTokenType::endl},
		{ope}, // assert
		{eTokenType::endl},
		{eTokenType::endl},
		{eTokenType::endl},
		{eTokenType::endl},
		{eTokenType::endl},
		{eTokenType::endl},
		{eTokenType::endl},
		{eTokenType::endl},
		{eTokenType::endl},
		{eTokenType::endl},
		{eTokenType::endl},
		{instr}
	}};

	this->p_ex_seq = {{
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::missingNumberException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::missingNumberException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::forbiddenTokenException,
		eExceptionType::missingInstructionException
	}};
}