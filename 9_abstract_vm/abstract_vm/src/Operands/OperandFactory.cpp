#include "Operands/OperandFactory.hpp"
#include "Operands/Operand.tpp"
#include "Exceptions/Exceptions.hpp"
#include <limits.h>
#include <cfenv>

OperandFactory::OperandFactory(void) {
    return;
}

OperandFactory::~OperandFactory(void) {
    return;
}

IOperand const* OperandFactory::createInt8( std::string const& value ) const {
    double nb = std::stoi(const_cast<std::string &>(value));
    // TODO Overflow / underflow
    if (nb > std::pow(2, 7) || nb < - std::pow(2, 7))
        throw overflowException(0);
    Operand<char> *ope = new Operand<char>(nb, eOperandType::Int8, 0);
    return ope;
}

IOperand const* OperandFactory::createInt16( std::string const& value ) const {
    double nb = std::stoi(const_cast<std::string &>(value));
    // TODO Overflow / underflow
    if (nb > std::pow(2, 15) || nb < - std::pow(2, 15))
        throw overflowException(0);
    Operand<short> *ope = new Operand<short>(nb, eOperandType::Int16, 0);
    return ope;
}

IOperand const* OperandFactory::createInt32( std::string const& value ) const {
    double nb = std::stoi(const_cast<std::string &>(value));
    // TODO Overflow / underflow
    if (nb > INT_MAX || nb < INT_MIN)
        throw overflowException(0);
    Operand<int> *ope = new Operand<int>(nb, eOperandType::Int32, 0);
    return ope;
}

IOperand const* OperandFactory::createFloat( std::string const& value ) const {
    float nb = 0;

    try {
        nb = std::stof(const_cast<std::string &>(value));
    }
    catch (const std::out_of_range& e) {
        throw overflowException(0);
    }
    Operand<float> *ope = new Operand<float>(nb, eOperandType::Float, 0);
    return ope;
}

IOperand const* OperandFactory::createDouble( std::string const& value ) const {
    double nb = 0;

    try {
        nb = std::stod(const_cast<std::string &>(value));
    }
    catch (const std::out_of_range& e) {
        throw overflowException(0);
    }
    Operand<double> *ope = new Operand<double>(nb, eOperandType::Double, 0);
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
