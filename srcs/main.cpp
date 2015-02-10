// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hlecuyer <hlecuyer@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/02/10 12:25:28 by hlecuyer          #+#    #+#             //
//   Updated: 2015/02/10 12:25:30 by hlecuyer         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char const *argv[])
{
    std::vector<Parser> parser;


    if (argc == 2)
        parser[0] = Parser();
    else
    {
        for (int i = 1; i < argc; i++)
        {
            parser[i - 1] = Parser(argv[i]);
            //process.execute(parser[i - 1].parseFile());
        }
    }
    return 0;
}