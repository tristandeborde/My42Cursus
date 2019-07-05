/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:49:20 by tdeborde          #+#    #+#             */
/*   Updated: 2019/06/06 15:03:23 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVMInput.hpp"

int main(int ac, char const **av)
{
    AVMInput input(ac, av);

    std::cout << input.getContent() << std::endl;
    return 0;
}
