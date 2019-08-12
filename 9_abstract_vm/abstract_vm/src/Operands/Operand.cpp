#include "Operand.tpp"

template <typename T>
IOperand const *Operand<T>::operator%( IOperand const & rhs ) const {
    Operand<T> *res = new Operand<T>(*this);
    // TODO: handle over/underflows
    res->p_nb %= dynamic_cast<const Operand<T> &>(rhs).p_nb;
    res->p_value = std::to_string(res->p_nb);
    return (static_cast<IOperand *>(res));
} // Int mod
template <>
IOperand const *Operand<float>::operator%( IOperand const & rhs ) const {
    Operand<float> *res = new Operand<float>(*this);
    // TODO: handle over/underflows
    res->p_nb = std::fmod(res->p_nb, dynamic_cast<const Operand<float> &>(rhs).p_nb);
    res->p_value = std::to_string(res->p_nb);
    return (static_cast<IOperand *>(res));
} // double mod
template <>
IOperand const *Operand<double>::operator%( IOperand const & rhs ) const {
    Operand<double> *res = new Operand<double>(*this);
    // TODO: handle over/underflows
    res->p_nb = std::fmod(res->p_nb, dynamic_cast<const Operand<double> &>(rhs).p_nb);
    res->p_value = std::to_string(res->p_nb);
    return (static_cast<IOperand *>(res));
} // double mod

// #############################################################################
// Overflow/Underflow ##########################################################

template <typename T>
void Operand<T>::checkOverflow(T var)
{
    (void)var;
    return;
}

template <>
void Operand<int>::checkOverflow(int var)
{
    (void)var;
    return;
}

template <typename T>
void Operand<T>::checkUnderflow(T var)
{
    (void)var;
    return;
}

template <>
void Operand<int>::checkUnderflow(int var)
{
    (void)var;
    return;
}


// #############################################################################
// Getters/Setters #############################################################

template <typename T>
T Operand<T>::getNb(void) {
    return this->p_nb;
}

template class Operand<char>;
template class Operand<short>;
template class Operand<int>;
template class Operand<float>;
template class Operand<double>;
