#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <string>

class ParserException: public std::exception
{
    public:
        const char* what() const throw();

        ParserException(int line_nb, std::string err_msg);
        virtual ~ParserException(void) {} ;
        ParserException & operator=(const ParserException &) = delete;
        ParserException(const ParserException &);
    private:
        int         p_line_nb;
        std::string p_error_msg;
};

class badSyntaxException: public ParserException
{
    public:
        badSyntaxException(int line_nb);
        ~badSyntaxException(void);
};

class invalidNumberException: public ParserException
{
    public:
        invalidNumberException(int line_nb);
        virtual ~invalidNumberException(void);
};

class missingNumberException: public ParserException
{
    public:
        missingNumberException(int line_nb);
        virtual ~missingNumberException(void);
};

class overflowException: public ParserException
{
    public:
        overflowException(int line_nb);
        virtual ~overflowException(void);
};

class forbiddenInstructionException: public ParserException
{
    public:
        forbiddenInstructionException(int line_nb);
        virtual ~forbiddenInstructionException(void);
};

class noExitException: public ParserException
{
    public:
        noExitException(int line_nb);
        virtual ~noExitException(void);
};

class GenericException: public std::exception
{
    public:
        virtual const char * what() const throw();
};

#endif
