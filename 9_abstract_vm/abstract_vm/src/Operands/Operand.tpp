#ifndef OPERAND_TPP
# define OPERAND_TPP

# include "Operands/IOperand.hpp"

template <typename T>
class Operand: public IOperand {

    public:

// #############################################################################
// Coplien functions ###########################################################

        Operand(T nb, std::string value, eOperandType type, int precision)
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
            Operand<T> *res = new Operand<T>(*this);
            // TODO: handle over/underflows
            res->p_nb += dynamic_cast<const Operand<T> &>(rhs).p_nb;
            res->p_value = std::to_string(res->p_nb);
            return (res);
        } // Sum
        IOperand const *operator-( IOperand const & rhs ) const {
            Operand<T> *res = new Operand<T>(*this);
            // TODO: handle over/underflows
            res->p_nb -= dynamic_cast<const Operand<T> &>(rhs).p_nb;
            res->p_value = std::to_string(res->p_nb);
            return (static_cast<IOperand *>(res));
        } // Difference
        IOperand const *operator*( IOperand const & rhs ) const {
            Operand<T> *res = new Operand<T>(*this);
            // TODO: handle over/underflows
            res->p_nb *= dynamic_cast<const Operand<T> &>(rhs).p_nb;
            res->p_value = std::to_string(res->p_nb);
            return (static_cast<IOperand *>(res));
        } // Product
        IOperand const *operator/( IOperand const & rhs ) const {
            Operand<T> *res = new Operand<T>(*this);
            // TODO: handle over/underflows
            res->p_nb /= dynamic_cast<const Operand<T> &>(rhs).p_nb;
            res->p_value = std::to_string(res->p_nb);
            return (static_cast<IOperand *>(res));
        } // Quotient
        // template <typename T>
        // IOperand const *operator%( IOperand const & rhs ) const {
        //     return ( this->mod(dynamic_cast<const Operand<T> &>(rhs)) );
        // }
        IOperand const *operator%( IOperand const & rhs ) const;

        // IOperand const *mod( Operand<T> const & rhs ) const;


// #############################################################################
// Overflow/Underflow ##########################################################

        void checkOverflow(T var);
        void checkUnderflow(T var);

// #############################################################################
// Overflow/Underflow ##########################################################

        T getNb(void);

    private:
        T               p_nb;
        std::string     p_value;
        eOperandType    p_type;
        int             p_precision;
};



#endif
