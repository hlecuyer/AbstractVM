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
#include "VirtualMachine.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

void    print_som(avm_instruct test)
{
	std::cout << test.name;
	if (test.instrType.type != "")
		std::cout << " [" << test.instrType.type << "] [" << test.instrType.value << "]";
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
//    std::vector<Parser> parser;
    Parser              parser;
    std::ifstream       stream;
    std::list<avm_instruct> test;
	// VirtualMachine				VM;

    if (argc == 1)
	{
        parser = Parser();
		parser.parseFile();
	}
    else
    {
        // for (int i = 1; i < argc; i++)
        // {
            // printf("la \n");
			stream.open(argv[1]);
            // printf("la \n");
			try
			{
				parser = Parser(&stream);
				// printf("la \n");
				parser.parseFile();
			}
			catch (Parser::ParsingException & e)
			{
				std::cout << e.what() << std::endl;
				std::exit(-1);
			}
			// std::cout << "****" << std::endl << "START PARSER DEBUG :" << std::endl;
			// parser.dumpDebug();
			// std::cout << "****" << std::endl;
            // printf("la \n");
            test = parser.getInstructionList();
            // printf("la \n");
			std::cout << "****" << std::endl << "START RETURN DEBUG :" << std::endl;
            for_each(test.begin(), test.end(), print_som);
			std::cout << "****" << std::endl;
			std::cout << "===============================" << std::endl;
			std::cout << "START EXEC" << std::endl;

			VirtualMachine				VM(parser.getInstructionList());
			// VM.addInstructions(parser.getInstructionList());
			VM.execute();
			std::cout << "===============================" << std::endl;
            // printf("la \n");
            // parser[i - 1] = Parser(argv[i]);
            //process.execute(parser[i - 1].parseFile());
    //     }
    }
    return 0;
}
