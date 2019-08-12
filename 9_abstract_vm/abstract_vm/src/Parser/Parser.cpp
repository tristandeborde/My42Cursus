#include "Parser/Parser.hpp"

Parser::Parser(const Lexer &src)
	: p_tokens(src.getTokens()), p_exceptions(src.getExceptions()) {
	this->p_initSeq();
	return;
}

Parser::~Parser(void) {
	return;
}

void	Parser::printExceptions(const std::vector<std::string> &exceptions)
{
	for (auto elem : exceptions)
		std::cout << elem << std::endl;
	throw (GenericException());
}

std::string 	Parser::getNumber(t_tokens_it it)
{
	std::smatch nb;
	if (!std::regex_search((*it).getToken(), nb, std::regex("\\(([-+]?\\d*\\.?\\d*)\\)"))
		|| !nb[1].str().size())
		throw (invalidNumberException((*it).getLineNb()));
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
	// Only lookback case is for eof token which must be preceded by exit 
	if (it != this->p_tokens.begin()
		&& (it - 1)->getType() != eTokenType::exit)
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
		throw ( this->p_ex_factory.create( this->p_ex_seq[static_cast<size_t>(type_it)], next->getLineNb() ) );

	// Token is valid so convert it to Instruction or Operand
	if (type_it <= eTokenType::print)
		this->addInstruction(type_it);
	else if (type_it <= eTokenType::dbl)
		this->addOperand(it);
}

void 	Parser::parse(void)
{
	for (t_tokens_it it = this->p_tokens.begin(); it != this->p_tokens.end(); it++) {
		try {
			if (it->getType() != eTokenType::eof)
				this->lookAhead(it);
			else
				this->lookBack(it);
		}
		catch (LexerParserException &e) {
			this->p_exceptions.push_back(e.what());
		}
	}
	if (this->p_exceptions.size())
		this->printExceptions(this->p_exceptions);
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
		eTokenType::int8,
		eTokenType::int16,
		eTokenType::int32,
		eTokenType::flt,
		eTokenType::dbl,
	};
	std::vector<eTokenType> instr;
	std::copy(all.begin(), all.begin() + 11, std::back_inserter(instr));
	std::vector<eTokenType> ope;
	std::copy(all.begin() + 11, all.end(), std::back_inserter(ope));

	this->p_ope_seq = {{
		{eTokenType::eof}, // exit
		{instr},
		{ope}, // push
		{instr},
		{ope}, // assert
		{instr},
		{instr},
		{instr},
		{instr},
		{instr},
		{instr},
		{instr},
		{instr},
		{instr},
		{instr},
		{instr}
	}};

	this->p_ex_seq = {{
		eExceptionType::misplacedExitException,
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
		eExceptionType::forbiddenTokenException
	}};
}


// void 	Parser::checkSequence(t_tokens_it it, t_tokens_it end)
// {
// 	t_tokens_it next = it + 1;
// 	eTokenType type = (*it).getType();

// 	// TODO: Change ugly if forest into sequence parsing:
// 	// 		check vector<eTokenType t> Tokens against vector<vector<eTokenType t>> Valid_Sequences

// 	// IF INSTR == (Push || Assert) : Look ahead to check if next is number
// 	if (type == eTokenType::push || type == eTokenType::assert) {
// 		if (next == end || (*next).getType() < eTokenType::int8)
// 			throw (missingNumberException((*it).getLineNb()));
// 	}
// 	// IF NB || INSTR != (Push || Assert) : Look ahead to check if \n
// 	if (type != eTokenType::endl && type != eTokenType::push && type != eTokenType::assert) {
// 		if (next == end || (*next).getType() != eTokenType::endl)
// 			throw (forbiddenTokenException((*it).getLineNb()));
// 	}
// 	// IF LAST != exit
// 	if (next->getType() == eTokenType::endl && (next + 1) == end && type != eTokenType::exit) {
// 		throw (noExitException((*it).getLineNb()));
// 	}
// }