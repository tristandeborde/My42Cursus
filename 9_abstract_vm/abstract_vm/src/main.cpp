/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:49:20 by tdeborde          #+#    #+#             */
/*   Updated: 2019/07/15 17:53:32 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVMInput.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int ac, char const **av)
{
    AVMInput    input(ac, av);
    Lexer       lexer;

    lexer.lex(input.getContent());
    Parser parser(lexer);
    parser.parse();
    return 0;
}
