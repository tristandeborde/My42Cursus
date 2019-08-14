#ifndef OPERAND_TPP
# define OPERAND_TPP

# include "Operands/IOperand.hpp"
# include "Operands/OperandFactory.hpp"

template <typename T>
class Operand: public IOperand {

    public:

// #############################################################################
// Coplien functions ###########################################################

        Operand(double nb, std::string value, eOperandType type, int precision)
            : p_nb(nb), p_value(value), p_type(type), p_precision(precision) {}
        Operand() = delete;
        Operand(const Operand &src)
            : p_nb(src.p_nb), p_value(src.p_value), p_type(src.p_type), p_precision(src.p_precision) {}
        Operand & operator=(const Operand &src) = delete;
        ~Operand(void) {};

// #############################################################################
// Getters/Setters #############################################################

        int           getPrecision(void) const {
            return (p_precision);
        } // Precision of the type of the instance

        eOperandType  getType(void) const {
            return (p_type);
        } // Type of the instance

        std::string const & toString(void) const {
            return (p_value);
        }// String representation of the instance

// #############################################################################
// Operator Overloads ##########################################################

        IOperand const *operator+( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stof(rhs.toString());
            OperandFactory fact;

            // TODO: handle over/underflows
            double nb = this->p_nb + rhs_val;
            auto ope_res = fact.createOperand(type_cast, std::to_string(nb));
            return (ope_res);
        } // Sum
        IOperand const *operator-( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stof(rhs.toString());
            OperandFactory fact;

            // TODO: handle over/underflows
            double nb = this->p_nb - rhs_val;
            std::string value = std::to_string(nb);
            auto ope_res = fact.createOperand(type_cast, std::to_string(nb));
            return (ope_res);
        } // Difference
        IOperand const *operator*( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stof(rhs.toString());
            OperandFactory fact;

            // TODO: handle over/underflows
            double nb = this->p_nb * rhs_val;
            std::string value = std::to_string(nb);
            auto ope_res = fact.createOperand(type_cast, std::to_string(nb));
            return (ope_res);
        } // Product
        IOperand const *operator/( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stof(rhs.toString());
            OperandFactory fact;

            // TODO: handle over/underflows
            double nb = this->p_nb / rhs_val;
            std::string value = std::to_string(nb);
            auto ope_res = fact.createOperand(type_cast, std::to_string(nb));
            return (ope_res);
        } // Quotient
        IOperand const *operator%( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stod(rhs.toString());
            OperandFactory fact;
            
            // TODO: handle over/underflows
            auto nb = std::fmod(this->p_nb, rhs_val);
            std::string value = std::to_string(nb);
            auto ope_res = fact.createOperand(type_cast, std::to_string(nb));
            return (ope_res);
        } // Mod


// #############################################################################
// Overflow/Underflow ##########################################################

        void checkOverflow(T var);
        void checkUnderflow(T var);

// #############################################################################
// Overflow/Underflow ##########################################################

        double getNb(void);

    private:
        double          p_nb;
        std::string     p_value;
        eOperandType    p_type;
        int             p_precision;
};



#endif
