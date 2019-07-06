/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:49:20 by tdeborde          #+#    #+#             */
/*   Updated: 2019/07/06 20:25:56 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVMInput.hpp"
#include "Lexer.hpp"

int main(int ac, char const **av)
{
    AVMInput    input(ac, av);
    Lexer       lex;

    lex.readLines(input.getContent());
    return 0;
}
