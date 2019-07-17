#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include "Operands/Operand.tpp"
# include "Operands/IOperand.hpp"

class OperandFactory {
    public:
        typedef IOperand const*(OperandFactory::* t_builder)(std::string const &value) const;

        OperandFactory(void);
        OperandFactory(const OperandFactory &) = delete;
        OperandFactory &operator=(const OperandFactory &) = delete;
        ~OperandFactory(void);
        IOperand const* createOperand( eOperandType type, std::string const& value ) const;

    private:
        IOperand const* createInt8( std::string const& value ) const;
        IOperand const* createInt16( std::string const& value ) const;
        IOperand const* createInt32( std::string const& value ) const;
        IOperand const* createFloat( std::string const& value ) const;
        IOperand const* createDouble( std::string const& value ) const;

        static t_builder p_builders[static_cast<int>(eOperandType::COUNT)];
};

#endif
