#ifndef OPERAND_TPP
# define OPERAND_TPP

# include "IOperand.hpp"

template <typename T>
class Operand: public IOperand {

    public:

        Operand(T nb, std::string value, eOperandType type, int precision)
            : p_nb(nb), p_value(value), p_type(type), p_precision(precision) {}
        Operand() = delete;
        Operand(const Operand &src)
            : p_nb(src.p_nb), p_value(src.p_value), p_type(src.p_type), p_precision(src.p_precision) {}
        Operand & operator=(const Operand &src) = delete;

        int           getPrecision(void) const {
            return (p_precision);
        }// Precision of the type of the instance

        eOperandType  getType(void) const {
            return (p_type);
        }// Type of the instance

        IOperand const *operator+( IOperand const & rhs ) const {
            Operand<T> *res = new Operand<T>(*this);
            // TODO: handle over/underflows
            res->p_nb += dynamic_cast<const Operand<T> &>(rhs).p_nb;
            res->p_value = std::to_string(res->p_nb);
            return res;
        } // Sum
        IOperand const *operator-( IOperand const & rhs ) const {
            Operand<T> *res = new Operand<T>(*this);
            // TODO: handle over/underflows
            res->p_nb -= dynamic_cast<const Operand<T> &>(rhs).p_nb;
            res->p_value = std::to_string(res->p_nb);
            return res;
        } // Difference
        IOperand const *operator*( IOperand const & rhs ) const {
            Operand<T> *res = new Operand<T>(*this);
            // TODO: handle over/underflows
            res->p_nb *= dynamic_cast<const Operand<T> &>(rhs).p_nb;
            res->p_value = std::to_string(res->p_nb);
            return res;
        } // Product
        IOperand const *operator/( IOperand const & rhs ) const {
            Operand<T> *res = new Operand<T>(*this);
            // TODO: handle over/underflows
            res->p_nb /= dynamic_cast<const Operand<T> &>(rhs).p_nb;
            res->p_value = std::to_string(res->p_nb);
            return res;
        } // Quotient
        IOperand const *operator%( IOperand const & rhs ) const {
            Operand<T> *res = new Operand<T>(*this);
            // TODO: handle over/underflows
            res->p_nb %= dynamic_cast<const Operand<T> &>(rhs).p_nb;
            res->p_value = std::to_string(res->p_nb);
            return res;
        } // Modulo

        std::string const & toString(void) const {
            return (p_value);
        }// String representation of the instance

        ~Operand(void) {};

    private:
        T               p_nb;
        std::string     p_value;
        eOperandType    p_type;
        int             p_precision;
};

#endif
