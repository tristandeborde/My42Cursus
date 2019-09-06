#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <string>
#include "Lexer/eTokenType.hpp"

class LexerParserException: public std::exception
{
    public:
        const char* what() const throw();

        LexerParserException(int line_nb, std::string err_msg);
        virtual ~LexerParserException(void) {} ;
        LexerParserException & operator=(const LexerParserException &) = delete;
        LexerParserException(const LexerParserException &);
    private:
        int         p_line_nb;
        std::string p_error_msg;
};

class badSyntaxException: public LexerParserException
{
    public:
        badSyntaxException(int line_nb);
        ~badSyntaxException(void);
};

class invalidNumberException: public LexerParserException
{
    public:
        invalidNumberException(int line_nb);
        virtual ~invalidNumberException(void);
};

class missingNumberException: public LexerParserException
{
    public:
        missingNumberException(int line_nb);
        virtual ~missingNumberException(void);
};

class overflowException: public LexerParserException
{
    public:
        overflowException(int line_nb);
        virtual ~overflowException(void);
};

class underflowException: public LexerParserException
{
    public:
        underflowException(int line_nb);
        virtual ~underflowException(void);
};

class forbiddenTokenException: public LexerParserException
{
    public:
        forbiddenTokenException(int line_nb);
        virtual ~forbiddenTokenException(void);
};

class noExitException: public LexerParserException
{
    public:
        noExitException(int line_nb);
        virtual ~noExitException(void);
};

class misplacedExitException: public LexerParserException
{
    public:
        misplacedExitException(int line_nb);
        virtual ~misplacedExitException(void);
};

class assertException: public std::exception
{
    public:
        const char* what() const throw();
};

class GenericException: public std::exception
{
    public:
        virtual const char * what() const throw();
};

class ExceptionFactory
{
    public:
        ExceptionFactory(void);
        ~ExceptionFactory(void);
        ExceptionFactory(const ExceptionFactory &) = delete;
        ExceptionFactory & operator=(const ExceptionFactory &) = delete;

        typedef LexerParserException (ExceptionFactory::*t_builder)(int line_nb) const;
        
        LexerParserException createMissingNumber(int line_nb) const;
        LexerParserException createForbiddenInstruction(int line_nb) const;
        LexerParserException createNoExit(int line_nb) const;
        LexerParserException createMisplacedExit(int line_nb) const;
        LexerParserException create(eExceptionType type, int line_nb) const;
};


#endif
