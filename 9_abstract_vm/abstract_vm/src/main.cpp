/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:49:20 by tdeborde          #+#    #+#             */
/*   Updated: 2019/11/06 15:19:33 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer/AVMInput.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Exceptions/Exceptions.hpp"
#include "Operands/IOperand.hpp"
#include "Processor/Processor.hpp"

int main(int ac, char const **av) {
    AVMInput                        input(ac, av);
    Lexer                           lexer;
    Processor                       proc;

    try {
        input.read();
    }
    catch (InputException &e)
    {
	    std::cout << e.what() << std::endl;
        return 1;
    }
    lexer.lex(input.getContent());
    Parser parser(lexer);
    if (!parser.parse()) 
        return 1;
    if (!proc.run(parser.getInstructions()))
        return 1;
    return 0;
}