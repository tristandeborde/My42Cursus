#include "LexerExceptions.hpp"

const char* LexerException::what() const throw()
{
    std::string statement = "Line ";
    statement += std::to_string(this->p_line_nb);
    statement += ": syntax error, " + this->p_error_msg;
    return statement.c_str();
}

LexerException::LexerException(int line_nb, std::string err_msg):
    p_line_nb(line_nb),
    p_error_msg(err_msg)
{
    return;
}

badSyntaxException::badSyntaxException(int line_nb):
    LexerException(line_nb, "no match found for expression.")
{
    return;
}

missingParenthesisException::missingParenthesisException(int line_nb):
    LexerException(line_nb, "missing parenthesis after value call.")
{
    return;
}

isolatedVariableException::isolatedVariableException(int line_nb):
    LexerException(line_nb, "isolated variable type keyword has no assigned value.")
{
    return;
}

badSyntaxException::~badSyntaxException(void)
{
    return;
}

missingParenthesisException::~missingParenthesisException(void)
{
    return;
}

isolatedVariableException::~isolatedVariableException(void)
{
    return;
}
