/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:49:20 by tdeborde          #+#    #+#             */
/*   Updated: 2019/07/19 00:02:37 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer/AVMInput.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Operands/IOperand.hpp"
#include "Processor/Processor.hpp"
#include <stack>

int main(int ac, char const **av)
{
    AVMInput                            input(ac, av);
    Lexer                               lexer;
    Processor                           proc;
    std::stack<IOperand const *>        pile;

    lexer.lex(input.getContent());
    Parser parser(lexer);
    parser.parse();
    proc.run(parser.getInstructions());
    return 0;
}
