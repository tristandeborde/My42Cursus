#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <string>
#include "Lexer/eTokenType.hpp"

class LexerParserException: public std::exception
{
    public:
        const char* what() const throw();

        LexerParserException(int line_nb, std::string err_msg);
        LexerParserException() = delete;
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
        badSyntaxException() = delete;
        badSyntaxException & operator=(const badSyntaxException &) = delete;
        badSyntaxException(const badSyntaxException &); 
        virtual ~badSyntaxException(void);
};

class invalidNumberException: public LexerParserException
{
    public:
        invalidNumberException(int line_nb);
        invalidNumberException() = delete;
        invalidNumberException & operator=(const invalidNumberException &) = delete;
        invalidNumberException(const invalidNumberException &); 
        virtual ~invalidNumberException(void);
};

class missingNumberException: public LexerParserException
{
    public:
        missingNumberException(int line_nb);
        missingNumberException() = delete;
        missingNumberException & operator=(const missingNumberException &) = delete;
        missingNumberException(const missingNumberException &); 
        virtual ~missingNumberException(void);
};

class overflowException: public LexerParserException
{
    public:
        overflowException(int line_nb);
        overflowException() = delete;
        overflowException & operator=(const overflowException &) = delete;
        overflowException(const overflowException &); 
        virtual ~overflowException(void);
};

class underflowException: public LexerParserException
{
    public:
        underflowException(int line_nb);
        underflowException() = delete;
        underflowException & operator=(const underflowException &) = delete;
        underflowException(const underflowException &);
        virtual ~underflowException(void);
};

class forbiddenTokenException: public LexerParserException
{
    public:
        forbiddenTokenException(int line_nb);
        forbiddenTokenException() = delete;
        forbiddenTokenException & operator=(const forbiddenTokenException &) = delete;
        forbiddenTokenException(const forbiddenTokenException &);
        virtual ~forbiddenTokenException(void);
};

class noExitException: public LexerParserException
{
    public:
        noExitException(int line_nb);
        noExitException() = delete;
        noExitException & operator=(const noExitException &) = delete;
        noExitException(const noExitException &);
        virtual ~noExitException(void);
};

class misplacedExitException: public LexerParserException
{
    public:
        misplacedExitException(int line_nb);
        misplacedExitException() = delete;
        misplacedExitException & operator=(const misplacedExitException &) = delete;
        misplacedExitException(const misplacedExitException &);
        virtual ~misplacedExitException(void);
};

class assertException: public std::exception
{
    public:
        assertException(void) = default;
        assertException & operator=(const assertException &) = delete;
        assertException(const assertException &);
        const char* what() const throw();
};

class GenericException: public std::exception
{
    public:
        GenericException(void) = default;
        GenericException & operator=(const GenericException &) = delete;
        GenericException(const GenericException &);
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
