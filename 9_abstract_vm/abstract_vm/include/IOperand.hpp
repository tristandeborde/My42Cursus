/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:57:25 by tdeborde          #+#    #+#             */
/*   Updated: 2019/06/06 12:31:37 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

classIOperand{

    public:

        virtual int getPrecision(void)const= 0;// Precision of the type of the instance
        virtual eOperandType  getType(void)const= 0;// Type of the instance
        virtual IOperandconst *operator+( IOperandconst& rhs )const= 0;// Sum
        virtual IOperandconst *operator-( IOperandconst& rhs )const= 0;// Difference
        virtual IOperandconst *operator*( IOperandconst& rhs )const= 0;// Product
        virtual IOperandconst *operator/( IOperandconst& rhs )const= 0;// Quotient
        virtual IOperandconst*operator%( IOperandconst& rhs )const= 0;// Modulo

        virtual std::stringconst & toString(void)const= 0;// String representation of the instance

        virtual ~IOperand(void) {}
};
