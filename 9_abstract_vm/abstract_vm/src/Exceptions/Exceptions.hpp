#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <string>
# include "Lexer/eTokenType.hpp"

class InputException: public std::exception
{
    public:
        const char* what() const throw();

        InputException(std::string err_msg);
        InputException() = delete;
        virtual ~InputException(void) {} ;
        InputException & operator=(const InputException &) = delete;
        InputException(const InputException &) = default;

    private:
        std::string p_error_msg;
};

class noFileException: public InputException
{
    public:
        noFileException();
        noFileException & operator=(const noFileException &) = delete;
        noFileException(const noFileException &) = default;
        virtual ~noFileException(void);
};

class badUsageException: public InputException
{
    public:
        badUsageException();
        badUsageException & operator=(const badUsageException &) = delete;
        badUsageException(const badUsageException &) = default;
        virtual ~badUsageException(void);
};


class AVMException: public std::exception
{
    public:
        const char* what() const throw();

        AVMException(int line_nb, std::string err_msg);
        AVMException() = delete;
        virtual ~AVMException(void) {} ;
        AVMException & operator=(const AVMException &) = delete;
        AVMException(const AVMException &) = default;
    private:
        int         p_line_nb;
        std::string p_error_msg;
};

class assertException: public AVMException
{
    public:
        assertException();
        assertException & operator=(const assertException &) = delete;
        assertException(const assertException &) = default;
        virtual ~assertException(void);
};

class printTypeException: public AVMException
{
    public:
        printTypeException();
        printTypeException & operator=(const printTypeException &) = delete;
        printTypeException(const printTypeException &) = default;
        virtual ~printTypeException(void);
};

class pileSizeException: public AVMException
{
    public:
        pileSizeException(std::string ope_name, int req_size);
        pileSizeException() = delete;
        pileSizeException & operator=(const pileSizeException &) = delete;
        pileSizeException(const pileSizeException &) = default;
        virtual ~pileSizeException(void);
};

class pileEmptyException: public AVMException
{
    public:
        pileEmptyException(std::string ope_name);
        pileEmptyException() = delete;
        pileEmptyException & operator=(const pileEmptyException &) = delete;
        pileEmptyException(const pileEmptyException &) = default;
        virtual ~pileEmptyException(void);
};

class nullDenominator: public AVMException
{
    public:
        nullDenominator();
        nullDenominator & operator=(const nullDenominator &) = delete;
        nullDenominator(const nullDenominator &) = default;
        virtual ~nullDenominator(void);
};

class badSyntaxException: public AVMException
{
    public:
        badSyntaxException(int line_nb, const std::string &badToken);
        badSyntaxException() = delete;
        badSyntaxException & operator=(const badSyntaxException &) = delete;
        badSyntaxException(const badSyntaxException &) = default; 
        virtual ~badSyntaxException(void);
};

class invalidNumberException: public AVMException
{
    public:
        invalidNumberException(int line_nb, const std::string &token);
        invalidNumberException() = delete;
        invalidNumberException & operator=(const invalidNumberException &) = delete;
        invalidNumberException(const invalidNumberException &) = default; 
        virtual ~invalidNumberException(void);
};

class missingNumberException: public AVMException
{
    public:
        missingNumberException(int line_nb);
        missingNumberException() = delete;
        missingNumberException & operator=(const missingNumberException &) = delete;
        missingNumberException(const missingNumberException &) = default; 
        virtual ~missingNumberException(void);
};

class missingInstructionException: public AVMException
{
    public:
        missingInstructionException(int line_nb);
        missingInstructionException() = delete;
        missingInstructionException & operator=(const missingInstructionException &) = delete;
        missingInstructionException(const missingInstructionException &) = default; 
        virtual ~missingInstructionException(void);
};

class overflowException: public AVMException
{
    public:
        overflowException(int line_nb);
        overflowException() = delete;
        overflowException & operator=(const overflowException &) = delete;
        overflowException(const overflowException &) = default; 
        virtual ~overflowException(void);
};

class underflowException: public AVMException
{
    public:
        underflowException(int line_nb);
        underflowException() = delete;
        underflowException & operator=(const underflowException &) = delete;
        underflowException(const underflowException &) = default;
        virtual ~underflowException(void);
};

class forbiddenTokenException: public AVMException
{
    public:
        forbiddenTokenException(int line_nb);
        forbiddenTokenException() = delete;
        forbiddenTokenException & operator=(const forbiddenTokenException &) = delete;
        forbiddenTokenException(const forbiddenTokenException &) = default;
        virtual ~forbiddenTokenException(void);
};

class noExitException: public AVMException
{
    public:
        noExitException(int line_nb);
        noExitException() = delete;
        noExitException & operator=(const noExitException &) = delete;
        noExitException(const noExitException &) = default;
        virtual ~noExitException(void);
};

class misplacedExitException: public AVMException
{
    public:
        misplacedExitException(int line_nb);
        misplacedExitException() = delete;
        misplacedExitException & operator=(const misplacedExitException &) = delete;
        misplacedExitException(const misplacedExitException &) = default;
        virtual ~misplacedExitException(void);
};

class ExceptionFactory
{
    public:
        ExceptionFactory(void);
        ~ExceptionFactory(void);
        ExceptionFactory(const ExceptionFactory &) = delete;
        ExceptionFactory & operator=(const ExceptionFactory &) = delete;

        typedef AVMException (ExceptionFactory::*t_builder)(int line_nb) const;
        
        AVMException createMissingNumber(int line_nb) const;
        AVMException createMissingInstruction(int line_nb) const;
        AVMException createForbiddenInstruction(int line_nb) const;
        AVMException createNoExit(int line_nb) const;
        AVMException createMisplacedExit(int line_nb) const;
        AVMException create(eExceptionType type, int line_nb) const;
};


#endif
