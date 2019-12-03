#include "Operands/OperandFactory.hpp"
#include "Operands/Operand.hpp"
#include "Exceptions/Exceptions.hpp"
#include <limits>
#include <cstdlib>

OperandFactory::OperandFactory(void) {
    return;
}

OperandFactory::~OperandFactory(void) {
    return;
}

IOperand const* OperandFactory::createInt8( std::string const& value ) const {
    try {
        int nb = std::stoi(const_cast<std::string &>(value));
        if (nb > std::pow(2, 7) - 1 || nb < - std::pow(2, 7))
            throw overflowException(0);
        Operand<char> *ope = new Operand<char>(nb, eOperandType::Int8, 0);
        return ope;
    }
    catch (const std::out_of_range& e) {
        throw overflowException(0);
    }
}

IOperand const* OperandFactory::createInt16( std::string const& value ) const {
    try {
        int nb = std::stoi(const_cast<std::string &>(value));
        if (nb > std::pow(2, 15) - 1 || nb < - std::pow(2, 15))
            throw overflowException(0);
        Operand<short> *ope = new Operand<short>(nb, eOperandType::Int16, 0);
        return ope;
    }
    catch (const std::out_of_range& e) {
        throw overflowException(0);
    }
}

IOperand const* OperandFactory::createInt32( std::string const& value ) const {
    try {
        long nb = std::stol(const_cast<std::string &>(value));
        if (nb > INT_MAX || nb < INT_MIN)
            throw overflowException(0);
        Operand<int> *ope = new Operand<int>(nb, eOperandType::Int32, 0);
        return ope;
    }
    catch (const std::out_of_range& e) {
       throw overflowException(0); 
    }
}

IOperand const* OperandFactory::createFloat( std::string const& value ) const {
    char *endptr = NULL;
    errno = 0;
    float res = std::strtof(value.c_str(), &endptr);
    if (errno == ERANGE && std::abs(res) > 1) {
        throw overflowException(0);
    }
    if (errno == ERANGE && std::abs(res) < 1) {
        throw underflowException(0);
    }
    Operand<float> *ope = new Operand<float>(res, eOperandType::Float, 0);
    return ope;
}

IOperand const* OperandFactory::createDouble( std::string const& value ) const {
    char *endptr = NULL;
    errno = 0;
    double res = std::strtod(value.c_str(), &endptr);
    if (errno == ERANGE && std::abs(res) > 1) {
        throw overflowException(0);
    }
    if (errno == ERANGE && std::abs(res) < 1) {
        throw underflowException(0);
    }
    Operand<double> *ope = new Operand<double>(res, eOperandType::Double, 0);
    return ope;
}

IOperand const*OperandFactory::createOperand( eOperandType const type, std::string const& value ) const {
    t_builder p_builders[static_cast<int>(eOperandType::COUNT)] =
        {
            &OperandFactory::createInt8,
            &OperandFactory::createInt16,
            &OperandFactory::createInt32,
            &OperandFactory::createFloat,
            &OperandFactory::createDouble
        };

    return ( (this->*(p_builders[static_cast<int>(type)])) (value) );
}
