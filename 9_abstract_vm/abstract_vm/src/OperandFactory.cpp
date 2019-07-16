#include "OperandFactory.hpp"

OperandFactory::OperandFactory(void) {
    return;
}

OperandFactory::~OperandFactory(void) {
    return;
}

IOperand const* OperandFactory::createInt8( std::string const& value ) const {
    int nb = std::stoi(value);
    Operand<int> *ope = new Operand<int>(nb, value, eOperandType::Int8, 0);
    return ope;
}

IOperand const* OperandFactory::createInt16( std::string const& value ) const {
    int nb = std::stoi(value);
    Operand<int> *ope = new Operand<int>(nb, value, eOperandType::Int16, 0);
    return ope;
}

IOperand const* OperandFactory::createInt32( std::string const& value ) const {
    int nb = std::stoi(value);
    Operand<int> *ope = new Operand<int>(nb, value, eOperandType::Int32, 0);
    return ope;
}

IOperand const* OperandFactory::createFloat( std::string const& value ) const {
    int nb = std::stof(value);
    Operand<int> *ope = new Operand<int>(nb, value, eOperandType::Float, 0);
    return ope;
}

IOperand const* OperandFactory::createDouble( std::string const& value ) const {
    int nb = std::stof(value);
    Operand<int> *ope = new Operand<int>(nb, value, eOperandType::Double, 0);
    return ope;
}

IOperand const*OperandFactory::createOperand( eOperandType type, std::string const& value ) const {
    t_builder p_builders[static_cast<int>(eOperandType::COUNT)] =
        {
            &OperandFactory::createInt8,
            &OperandFactory::createInt16,
            &OperandFactory::createInt32,
            &OperandFactory::createFloat,
            &OperandFactory::createInt8
        };

    return ( (this->*(p_builders[static_cast<int>(type)])) (value) );
}
