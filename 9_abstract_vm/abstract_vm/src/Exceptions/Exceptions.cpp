#include "Exceptions.hpp"


const char* assertException::what() const throw()
{
    std::string statement = "RUNTIME ERROR - assert is not true.";
    return statement.c_str();
}

const char* LexerParserException::what() const throw()
{
    std::string statement = "Line ";
    statement += std::to_string(this->p_line_nb);
    statement += ": " + this->p_error_msg;
    return statement.c_str();
}

LexerParserException::LexerParserException(int line_nb, std::string err_msg):
    p_line_nb(line_nb),
    p_error_msg(err_msg)
{
    return;
}

LexerParserException::LexerParserException(const LexerParserException &src):
    p_line_nb(src.p_line_nb),
    p_error_msg(src.p_error_msg)
{
    return;
}

badSyntaxException::badSyntaxException(int line_nb):
    LexerParserException(line_nb, "LEXER ERROR - no match found for expression.")
{
    return;
}

noExitException::noExitException(int line_nb):
    LexerParserException(line_nb, "PARSER ERROR - missing exit instruction at program's end.")
{
    return;
}

missingNumberException::missingNumberException(int line_nb):
    LexerParserException(line_nb, "PARSER ERROR - no value declared after instruction.")
{
    return;
}

invalidNumberException::invalidNumberException(int line_nb):
    LexerParserException(line_nb, "PARSER ERROR - value between parenthesis is not a number.")
{
    return;
}

overflowException::overflowException(int line_nb):
    LexerParserException(line_nb, "PARSER ERROR - overflow.")
{
    return;
}

underflowException::underflowException(int line_nb):
    LexerParserException(line_nb, "PARSER ERROR - underflow.")
{
    return;
}

forbiddenTokenException::forbiddenTokenException(int line_nb):
    LexerParserException(line_nb, "PARSER ERROR - instruction or operand is not at the right place.")
{
    return;
}

misplacedExitException::misplacedExitException(int line_nb):
    LexerParserException(line_nb, "PARSER ERROR - exit instruction is not at end of file.")
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

const char* GenericException::what() const throw()
{
    return ("Exiting: one/several lexing/parsing exception(s) found.");
}

ExceptionFactory::ExceptionFactory(void) {
    return;
}

ExceptionFactory::~ExceptionFactory(void) {
    return;
}

LexerParserException ExceptionFactory::createMissingNumber(int line_nb ) const {
    return missingNumberException(line_nb);
}

LexerParserException ExceptionFactory::createForbiddenInstruction(int line_nb ) const {
    return forbiddenTokenException(line_nb);
}

LexerParserException ExceptionFactory::createNoExit(int line_nb ) const {
    return noExitException(line_nb);
}

LexerParserException ExceptionFactory::createMisplacedExit(int line_nb ) const {
    return misplacedExitException(line_nb);
}

LexerParserException ExceptionFactory::create( eExceptionType type, int line_nb ) const {
    t_builder builders[static_cast<int>(eExceptionType::COUNT)] =
        {
            &ExceptionFactory::createMissingNumber,
            &ExceptionFactory::createForbiddenInstruction,
            &ExceptionFactory::createNoExit,
            &ExceptionFactory::createMisplacedExit
        };

    return ( (this->*(builders[static_cast<int>(type)])) (line_nb) );
}
