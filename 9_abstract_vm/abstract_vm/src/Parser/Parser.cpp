#include "Parser/Parser.hpp"

Parser::Parser(const Lexer &src)
	: p_tokens(src.getTokens()), p_exceptions(src.getExceptions()) {
	this->p_initSeq();
	return;
}

Parser::~Parser(void) {
	return;
}

// void	Parser::p_initSeq(void) {
// 	// BAD, only first if of the forest
// 	std::array <eTokenType, 5> numbers = 
// 	{
// 		eTokenType::int8,
// 		eTokenType::int16,
// 		eTokenType::int32,
// 		eTokenType::flt,
// 		eTokenType::dbl
// 		};
// 	this->p_ope_seq.emplace(eTokenType::assert, numbers);
// 	this->p_ope_seq.emplace(eTokenType::push, numbers);
// }

void	Parser::p_initSeq(void) {
	std::vector<eTokenType> numbers = 
	{
		eTokenType::int8,
		eTokenType::int16,
		eTokenType::int32,
		eTokenType::flt,
		eTokenType::dbl
		};
	std::vector<eTokenType> ope_instru = 
	{
		eTokenType::assert,
		eTokenType::push
		};
	this->p_ope_seq.emplace(eTokenType::assert, numbers);
	this->p_ope_seq.emplace(eTokenType::push, numbers);
	{op_instru, numbers, eTokenType::endl};
	{not_op_instru, eTokenType::endl};
	{{eTokenType::exit}, eTokenType::eof};
}

void	Parser::printExceptions(const std::vector<std::string> &exceptions)
{
	for (auto elem : exceptions)
		std::cout << elem << std::endl;
	throw (GenericException());
}

void 	Parser::checkSequence(t_tokens_it it, t_tokens_it end)
{
	t_tokens_it next = it + 1;
	eTokenType type = (*it).getType();

	// TODO: Change ugly if forest into sequence parsing:
	// 		check vector<eTokenType t> Tokens against vector<vector<eTokenType t>> Valid_Sequences

	;

	// IF INSTR == (Push || Assert) : Look ahead to check if next is number
	if (type == eTokenType::push || type == eTokenType::assert) {
		if (next == end || (*next).getType() < eTokenType::int8)
			throw (missingNumberException((*it).getLineNb()));
	}
	// IF NB || INSTR != (Push || Assert) : Look ahead to check if \n
	if (type != eTokenType::endl && type != eTokenType::push && type != eTokenType::assert) {
		if (next == end || (*next).getType() != eTokenType::endl)
			throw (forbiddenInstructionException((*it).getLineNb()));
	}
	// IF LAST != exit
	if (next->getType() == eTokenType::endl && (next + 1) == end && type != eTokenType::exit) {
		throw (noExitException((*it).getLineNb()));
	}
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
// 			throw (forbiddenInstructionException((*it).getLineNb()));
// 	}
// 	// IF LAST != exit
// 	if (next->getType() == eTokenType::endl && (next + 1) == end && type != eTokenType::exit) {
// 		throw (noExitException((*it).getLineNb()));
// 	}
// }

std::string 	Parser::getNumber(t_tokens_it it)
{
	std::smatch nb;
	#include <iostream>
	if (!std::regex_search((*it).getToken(), nb, std::regex("\\((\\d*\\.?\\d*)\\)"))
		|| !nb[1].str().size())
		throw (invalidNumberException((*it).getLineNb()));
	return nb[1].str();
}

void 	Parser::addOperand(t_tokens_it it, eTokenType type)
{
	// Extract nb string from token_str
	std::string 	nb = this->getNumber(it);

	// Check if token is operand -> attach to prev Instr
	eOperandType type_conv = static_cast<eOperandType>(static_cast<int>(type) - 11);

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

void 	Parser::parse(void)
{
	for (t_tokens_it it = this->p_tokens.begin(); it != this->p_tokens.end(); it++) {
		try {
			this->checkSequence(it, this->p_tokens.end());
			eTokenType type = (*it).getType();
			if (type == eTokenType::endl)
				continue;
			else if (type >= eTokenType::int8)
				this->addOperand(it, type);
			else if (type >= eTokenType::exit)
				this->addInstruction(type);
		}
		catch (ParserException &e) {
			this->p_exceptions.push_back(e.what());
		}
	}
	if (this->p_exceptions.size())
		this->printExceptions(this->p_exceptions);
}

std::vector<IInstruction *> const  &Parser::getInstructions(void) {
	return this->p_instructions;
}
