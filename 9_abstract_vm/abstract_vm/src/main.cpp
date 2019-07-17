/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:49:20 by tdeborde          #+#    #+#             */
/*   Updated: 2019/07/17 19:46:32 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer/AVMInput.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Operands/IOperand.hpp"
#include <stack>

int main(int ac, char const **av)
{
    AVMInput                            input(ac, av);
    Lexer                               lexer;
    std::stack<IOperand const *>        pile;

    lexer.lex(input.getContent());
    Parser parser(lexer);
    parser.parse();
    return 0;
}
