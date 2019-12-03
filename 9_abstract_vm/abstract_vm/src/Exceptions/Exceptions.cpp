#include "Exceptions.hpp"
#include <iostream>

// Input exceptions ############################################
// #############################################################

const char* InputException::what() const throw()
{
    std::string statement = "INPUT ERROR: ";
    statement += this->p_error_msg + "\n";
    statement += "Usage: ./avm [./input_file]";
    return statement.c_str();
}

InputException::InputException(std::string error_msg): p_error_msg(error_msg) 
{
    return;
}

noFileException::noFileException():
    InputException("entered filename could not be found.")
{
    return;
}

noFileException::~noFileException(void)
{
    return;
}

badUsageException::badUsageException():
    InputException("wrong number of arguments.")
{
    return;
}

badUsageException::~badUsageException(void)
{
    return;
}

// AVM exceptions #############################################
// #############################################################

const char* AVMException::what() const throw()
{
    std::string statement;

    if (this->p_line_nb) {
        statement = "LEXER/PARSER ERROR - Line ";
        statement += std::to_string(this->p_line_nb);
    }
    else
        statement = "RUNTIME ERROR";
    statement += ": " + this->p_error_msg + "\n";
    return statement.c_str();
}

AVMException::AVMException(int line_nb, std::string err_msg):
    p_line_nb(line_nb),
    p_error_msg(err_msg)
{
    return;
}

assertException::assertException():
    AVMException(0, "assert is not true.")
{
    return;
}

printTypeException::printTypeException():
    AVMException(0, "print called with wrong operand type, change type to int8.")
{
    return;
}

pileSizeException::pileSizeException(std::string ope_name, int req_size):
    AVMException(0, "pile size is lower than " + std::to_string(req_size) + ", operation " + ope_name + " not possible.")
{
    return;
}

pileEmptyException::pileEmptyException(std::string ope_name):
    AVMException(0, "pile is empty, operation " + ope_name + " not possible.")
{
    return;
}

nullDenominator::nullDenominator():
    AVMException(0, "denominator is null, cannot divide by zero.")
{
    return;
}

badSyntaxException::badSyntaxException(int line_nb, const std::string &badToken):
    AVMException(line_nb, "no match found for expression \"" + badToken + "\".")
{
    return;
}

noExitException::noExitException(int line_nb):
    AVMException(line_nb, "missing exit instruction at program's end.")
{
    return;
}

missingNumberException::missingNumberException(int line_nb):
    AVMException(line_nb, "the previous instruction is missing a valid operand.")
{
    return;
}

missingInstructionException::missingInstructionException(int line_nb):
    AVMException(line_nb + 1, "missing instruction at the beginning of line.")
{
    return;
}

invalidNumberException::invalidNumberException(int line_nb, const std::string &token):
    AVMException(line_nb, "no valid number found for operand \"" + token + "\".")
{
    return;
}

overflowException::overflowException(int line_nb):
    AVMException(line_nb, "overflow on operand value.")
{
    return;
}

underflowException::underflowException(int line_nb):
    AVMException(line_nb, "underflow on operand value.")
{
    return;
}

forbiddenTokenException::forbiddenTokenException(int line_nb):
    AVMException(line_nb, "unexpected token found before end of line.")
{
    return;
}

misplacedExitException::misplacedExitException(int line_nb):
    AVMException(line_nb, "exit instruction is not at end of file.")
{
    return;
}

assertException::~assertException(void)
{
    return;
}

printTypeException::~printTypeException(void)
{
    return;
}

pileSizeException::~pileSizeException(void)
{
    return;
}

pileEmptyException::~pileEmptyException(void)
{
    return;
}

nullDenominator::~nullDenominator(void)
{
    return;
}

badSyntaxException::~badSyntaxException(void)
{
    return;
}

missingNumberException::~missingNumberException(void)
{
    return;
}

missingInstructionException::~missingInstructionException(void)
{
    return;
}

invalidNumberException::~invalidNumberException(void)
{
    return;
}

overflowException::~overflowException(void)
{
    return;
}

underflowException::~underflowException(void)
{
    return;
}

forbiddenTokenException::~forbiddenTokenException(void)
{
    return;
}

noExitException::~noExitException(void)
{
    return;
}

misplacedExitException::~misplacedExitException(void)
{
    return;
}

ExceptionFactory::ExceptionFactory(void) {
    return;
}

ExceptionFactory::~ExceptionFactory(void) {
    return;
}

AVMException ExceptionFactory::createMissingNumber(int line_nb ) const {
    return missingNumberException(line_nb);
}

AVMException ExceptionFactory::createMissingInstruction(int line_nb ) const {
    return missingInstructionException(line_nb);
}

AVMException ExceptionFactory::createForbiddenInstruction(int line_nb ) const {
    return forbiddenTokenException(line_nb);
}

AVMException ExceptionFactory::createNoExit(int line_nb ) const {
    return noExitException(line_nb);
}

AVMException ExceptionFactory::createMisplacedExit(int line_nb ) const {
    return misplacedExitException(line_nb);
}

AVMException ExceptionFactory::create( eExceptionType type, int line_nb ) const {
    t_builder builders[static_cast<int>(eExceptionType::COUNT)] =
        {
            &ExceptionFactory::createMissingNumber,
            &ExceptionFactory::createMissingInstruction,
            &ExceptionFactory::createForbiddenInstruction,
            &ExceptionFactory::createNoExit,
            &ExceptionFactory::createMisplacedExit
        };

    return ( (this->*(builders[static_cast<int>(type)])) (line_nb) );
}
