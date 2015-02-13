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
#include <stdio.h>

void    print_som(avm_instruct test) {
        std::cout << test.name << std::endl;
        std::cout << test.instrType.type << std::endl << std::endl;
}

int main(int argc, char **argv)
{
//    std::vector<Parser> parser;
    Parser              parser;
    std::ifstream       stream;
    std::list<avm_instruct> test;

    if (argc == 1)
        parser = Parser();
    else
    {
        // for (int i = 1; i < argc; i++)
        // {
            printf("la \n");
			stream.open(argv[1]);
            printf("la \n");
            parser = Parser(&stream);
            printf("la \n");
            parser.parseFile();
            printf("la \n");
            test = parser.getInstructionList();
            printf("la \n");
            for_each(test.begin(), test.end(), print_som);
            printf("la \n");
            // parser[i - 1] = Parser(argv[i]);
            //process.execute(parser[i - 1].parseFile());
    //     }
    }
    return 0;
}
