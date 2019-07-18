#include "Operand.tpp"

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
