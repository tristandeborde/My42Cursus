#ifndef LEXER_EXCEPTIONS_HPP
# define LEXER_EXCEPTIONS_HPP

#include <string>

class LexerException: public std::exception
{
    public:
        const char* what() const throw();

        LexerException(int line_nb, std::string err_msg);
        virtual ~LexerException(void) {} ;
        LexerException & operator=(const LexerException &) = delete;
        LexerException(const LexerException &) = delete;
    private:
        int         p_line_nb;
        std::string p_error_msg;
};

class badSyntaxException: public LexerException
{
    public:
        badSyntaxException(int line_nb);
        ~badSyntaxException(void);
};

class missingParenthesisException: public LexerException
{
    public:
        missingParenthesisException(int line_nb);
        virtual ~missingParenthesisException(void);
};

class isolatedVariableException: public LexerException
{
    public:
        isolatedVariableException(int line_nb);
        virtual ~isolatedVariableException(void);
};

#endif
