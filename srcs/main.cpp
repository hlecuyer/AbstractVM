// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hlecuyer <hlecuyer@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/02/10 12:25:28 by hlecuyer          #+#    #+#             //
//   Updated: 2015/03/25 13:39:51 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "parser.hpp"
#include "VirtualMachine.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdexcept>

int main(int argc, char **argv)
{
    Parser *            parser;
	VirtualMachine *	VM;
    std::ifstream       stream;

	try
	{
		if (argc == 1)
		{
			parser = new Parser();
			parser->parseFile();
			// VirtualMachine				VM(parser->getInstructionList());
			VM = new VirtualMachine(parser->getInstructionList());
			VM->execute();
			delete parser;
			delete VM;
		}
		else
		{
			int i = 1;
			while (i < argc)
			{
				std::cout << "Abstract VM: executing file: *** " <<  argv[i] << " ***" << std::endl;
				try
				{
					stream.close();
					stream.open(argv[i]);
					if (stream.is_open())
					{
						parser = new Parser(&stream);
						parser->parseFile();
						// VirtualMachine				VM(parser->getInstructionList());
						VM = new VirtualMachine(parser->getInstructionList());
						VM->execute();
						delete parser;
						delete VM;
					}
					else
					{
						std::string ret = std::string("Failed to open file: ") + argv[i];
						throw std::runtime_error(ret);
					}
				}
				catch (std::exception & e)
				{
					std::cout << "Abstract VM: " << e.what() << std::endl;
					std::cout << "Type:    " << typeid(e).name() << std::endl;
					delete parser;
					delete VM;
				}
				i++;
				std::cout << "----------------------" << std::endl;
			}
		}
	}
	catch ( std::exception & e )
	{
		std::cout << "Abstract VM:" << e.what() << std::endl;
		exit(-1);
	}
    return (0);
}
