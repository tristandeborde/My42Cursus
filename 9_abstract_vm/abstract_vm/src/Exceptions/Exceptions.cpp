#include "Exceptions.hpp"

const char* ParserException::what() const throw()
{
    std::string statement = "Line ";
    statement += std::to_string(this->p_line_nb);
    statement += ": parsing error, " + this->p_error_msg;
    return statement.c_str();
}

ParserException::ParserException(int line_nb, std::string err_msg):
    p_line_nb(line_nb),
    p_error_msg(err_msg)
{
    return;
}

ParserException::ParserException(const ParserException &src):
    p_line_nb(src.p_line_nb),
    p_error_msg(src.p_error_msg)
{
    return;
}

badSyntaxException::badSyntaxException(int line_nb):
    ParserException(line_nb, "no match found for expression.")
{
    return;
}

missingNumberException::missingNumberException(int line_nb):
    ParserException(line_nb, "no value declared after instruction.")
{
    return;
}

invalidNumberException::invalidNumberException(int line_nb):
    ParserException(line_nb, "value between parenthesis is not a number.")
{
    return;
}

overflowException::overflowException(int line_nb):
    ParserException(line_nb, "argument is not a valid number.")
{
    return;
}

forbiddenInstructionException::forbiddenInstructionException(int line_nb):
    ParserException(line_nb, "forbidden instruction.")
{
    return;
}

noExitException::noExitException(int line_nb):
    ParserException(line_nb, "missing exit instruction at program's end.")
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

forbiddenInstructionException::~forbiddenInstructionException(void)
{
    return;
}

noExitException::~noExitException(void)
{
    return;
}

const char* GenericException::what() const throw()
{
    return ("Exiting: one/several lexing/parsing exception(s) found.");
}
