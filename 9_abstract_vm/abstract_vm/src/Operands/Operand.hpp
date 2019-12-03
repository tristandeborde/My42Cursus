#ifndef OPERAND_TPP
# define OPERAND_TPP

# include "Operands/IOperand.hpp"
# include "Operands/OperandFactory.hpp"
# include "Exceptions/Exceptions.hpp"
# include <cfenv>
# include <sstream>
# include <iomanip>

template <typename T>
class Operand: public IOperand {

    public:

// #############################################################################
// Coplien functions ###########################################################

        Operand(T nb, eOperandType type, int precision)
            : p_nb(nb), p_type(type), p_precision(precision) {
                std::string value;
                std::ostringstream tmp;
                value = std::to_string(nb);
                if (type >= eOperandType::Float) {
                    tmp.precision(std::numeric_limits<T>::digits10 + 3);
                    tmp << std::fixed << nb;
                    value = tmp.str();
                    value.erase(value.find_last_not_of('0') + 1, std::string::npos);
                }
                this->p_value = value;
            }
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
            return (this->p_value);
        }// String representation of the instance


// #############################################################################
// Operator Overloads ##########################################################

        IOperand const *operator+( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stod(rhs.toString());
            OperandFactory fact;

            // Handle over/underflows
            std::feclearexcept(FE_ALL_EXCEPT);
            double nb = this->p_nb + rhs_val;
            if ((bool)std::fetestexcept(FE_OVERFLOW))
                throw overflowException(0);
            if ((bool)std::fetestexcept(FE_UNDERFLOW))
                throw underflowException(0);

            // Store new string repr
            std::ostringstream tmp;
            std::string value;
            tmp << std::fixed;
            tmp << std::setprecision(std::numeric_limits<T>::digits10 + 1) << nb;
            value = tmp.str();

            auto ope_res = fact.createOperand(type_cast, value);
            return (ope_res);
        } // Sum
        IOperand const *operator-( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stod(rhs.toString());
            OperandFactory fact;

            // Handle over/underflows
            std::feclearexcept(FE_ALL_EXCEPT);
            double nb = this->p_nb - rhs_val;
            if ((bool)std::fetestexcept(FE_OVERFLOW))
                throw overflowException(0);
            if ((bool)std::fetestexcept(FE_UNDERFLOW))
                throw underflowException(0);

            // Store new string repr
            std::ostringstream tmp;
            std::string value;
            tmp << std::fixed;
            tmp << std::setprecision(std::numeric_limits<T>::digits10 + 1) << nb;
            value = tmp.str();

            auto ope_res = fact.createOperand(type_cast, value);
            return (ope_res);
        } // Difference
        IOperand const *operator*( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stod(rhs.toString());
            OperandFactory fact;

            // Handle over/underflows
            std::feclearexcept(FE_ALL_EXCEPT);
            double nb = this->p_nb * rhs_val;
            if ((bool)std::fetestexcept(FE_OVERFLOW))
                throw overflowException(0);
            if ((bool)std::fetestexcept(FE_UNDERFLOW))
                throw underflowException(0);

            // Store new string repr
            std::ostringstream tmp;
            std::string value;
            tmp << std::fixed;
            tmp << std::setprecision(std::numeric_limits<T>::digits10 + 1) << nb;
            value = tmp.str();

            auto ope_res = fact.createOperand(type_cast, value);
            return (ope_res);
        } // Product
        IOperand const *operator/( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stod(rhs.toString());
            OperandFactory fact;

            // Handle over/underflows
            std::feclearexcept(FE_ALL_EXCEPT);
            double nb = this->p_nb / rhs_val;
            if ((bool)std::fetestexcept(FE_OVERFLOW))
                throw overflowException(0);
            if ((bool)std::fetestexcept(FE_UNDERFLOW))
                throw underflowException(0);

            // Store new string repr
            std::ostringstream tmp;
            std::string value;
            tmp << std::fixed;
            tmp << std::setprecision(std::numeric_limits<T>::digits10 + 1) << nb;
            value = tmp.str();

            auto ope_res = fact.createOperand(type_cast, value);
            return (ope_res);
        } // Quotient
        IOperand const *operator%( IOperand const & rhs ) const {
            eOperandType type_cast = this->p_type >= rhs.getType() ? this->p_type : rhs.getType();
            double rhs_val = std::stod(rhs.toString());
            OperandFactory fact;
            
            // Handle over/underflows
            std::feclearexcept(FE_ALL_EXCEPT);
            auto nb = std::fmod(this->p_nb, rhs_val);
            if ((bool)std::fetestexcept(FE_OVERFLOW))
                throw overflowException(0);
            if ((bool)std::fetestexcept(FE_UNDERFLOW))
                throw underflowException(0);
            
            // Store new string repr
            std::ostringstream tmp;
            std::string value;
            tmp << std::fixed;
            tmp << std::setprecision(std::numeric_limits<T>::digits10 + 1) << nb;
            value = tmp.str();

            auto ope_res = fact.createOperand(type_cast, value);
            return (ope_res);
        } // Mod

    private:
        double          p_nb;
        std::string     p_value;
        eOperandType    p_type;
        int             p_precision;
};



#endif
