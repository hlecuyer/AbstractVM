/*=============================================================================
    Copyright (c) 2002-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
	=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  This sample demontrates a parser for a comma separated list of numbers.
//  The numbers are inserted in a vector using phoenix.
//
//  [ JDG May 10, 2002 ]    spirit1
//  [ JDG March 24, 2007 ]  spirit2
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    ///////////////////////////////////////////////////////////////////////////
    //  Our number list compiler
    ///////////////////////////////////////////////////////////////////////////
    //[tutorial_numlist2
    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<std::string>& v)
    {
        using qi::double_;
        using qi::phrase_parse;
        using qi::_1;
        using ascii::space;
        using phoenix::push_back;

        bool r = phrase_parse(first, last,

							  //  Begin grammar
            (lit("push") [boost::phoenix::push_back(boost::phoenix::ref(v), "push")]
            | lit("pop") [boost::phoenix::push_back(boost::phoenix::ref(v), "pop")]
            | lit("dump") [boost::phoenix::push_back(boost::phoenix::ref(v), "dump")]
            | lit("assert") [boost::phoenix::push_back(boost::phoenix::ref(v), "assert")]
            | lit("add") [boost::phoenix::push_back(boost::phoenix::ref(v), "add")]
            | lit("sub") [boost::phoenix::push_back(boost::phoenix::ref(v), "sub")]
            | lit("mul") [boost::phoenix::push_back(boost::phoenix::ref(v), "mul")]
            | lit("div") [boost::phoenix::push_back(boost::phoenix::ref(v), "div")]
            | lit("mod") [boost::phoenix::push_back(boost::phoenix::ref(v), "mod")]
            | lit("print") [boost::phoenix::push_back(boost::phoenix::ref(v), "print")]
            | lit("exit") [boost::phoenix::push_back(boost::phoenix::ref(v), "exit")]
            )
							  ,
							  //  End grammar

							  space);

        if (first != last) // fail if we did not get a full match
            return false;
        return r;
    }
    //]
}
//            (lit("push") [boost::phoenix::push_back(boost::phoenix::ref(v), "push")]
//             | lit("pop") [boost::phoenix::push_back(boost::phoenix::ref(v), "pop")]
//             | lit("dump") [boost::phoenix::push_back(boost::phoenix::ref(v), "dump")]
//             | lit("assert") [boost::phoenix::push_back(boost::phoenix::ref(v), "assert")]
//             | lit("add") [boost::phoenix::push_back(boost::phoenix::ref(v), "add")]
//             | lit("su b") [boost::phoenix::push_back(boost::phoenix::ref(v), "sub")]
//             | lit("mul") [boost::phoenix::push_back(boost::phoenix::ref(v), "mul")]
//             | lit("div") [boost::phoenix::push_back(boost::phoenix::ref(v), "div")]
//             | lit("mod") [boost::phoenix::push_back(boost::phoenix::ref(v), "mod")]
//             | lit("print") [boost::phoenix::push_back(boost::phoenix::ref(v), "print")]
//             | lit("exit") [boost::phoenix::push_back(boost::phoenix::ref(v), "exit")]
//             )

// //              instruction_
//                 >> boost::spirit::qi::eoi
//                 // lit("")
                // >> '{'
                // >>  int_ >> ','
                // >>  quoted_string >> ','
                // >>  quoted_string >> ','
                // >>  double_
                // >>  '}'
                ;
////////////////////////////////////////////////////////////////////////////
//  Main program
////////////////////////////////////////////////////////////////////////////
int
main()
{
	std::cout << "/////////////////////////////////////////////////////////\n\n";
	std::cout << "\t\tA comma separated list parser for Spirit...\n\n";
	std::cout << "/////////////////////////////////////////////////////////\n\n";

	std::cout << "Give me a comma separated list of numbers.\n";
	std::cout << "The numbers will be inserted in a vector of numbers\n";
	std::cout << "Type [q or Q] to quit\n\n";

	std::string str;
    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

		std::vector<std::string> v;
        if (client::parse_numbers(str.begin(), str.end(), v))
        {
			std::cout << "-------------------------\n";
			std::cout << "Parsing succeeded\n";
			std::cout << str << " Parses OK: " << std::endl;

            for (std::vector<std::string>::size_type i = 0; i < v.size(); ++i)
				std::cout << i << ": " << v[i] << std::endl;

			std::cout << "\n-------------------------\n";
        }
        else
        {
			std::cout << "-------------------------\n";
			std::cout << "Parsing failed\n";
			std::cout << "-------------------------\n";
        }
    }

	std::cout << "Bye... :-) \n\n";
    return 0;
}
