
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <list>

struct instructions_ : boost::spirit::qi::symbols<char, std::string>
{
	instructions_()
		{
            add
                ("pop"    , "pop")
                ("push"   , "push")
                ("dump"  , "dump")
                ("assert"   , "assert")
                ("add"    , "add")
                ("sub"   , "sub")
                ("mul"  , "mul")
                ("div" , "div")
                ("mod"   , "mod")
                ("print"   , "print")
                ("exit"   , "exit")
				;
		}

} instructions_;

class Aoperand
{
public:
	std::string		name;
};

typedef struct		s_instruct
{
	std::string		name;
	// Aoperand		*op;
}					t_instruct;

template <typename Iterator>
struct instruction_parser : boost::spirit::qi::grammar<Iterator, t_instruct(), boost::spirit::ascii::space_type>
{
	instruction_parser() : instruction_parser::base_type(start)
        {
            // using qi::int_;
            using boost::spirit::qi::lit;
            using boost::spirit::qi::double_;
            using boost::spirit::qi::lexeme;
            using boost::spirit::ascii::char_;

            instruction_string %= lexeme[ instructions_ ];

            start %=
				instruction_string
				>> boost::spirit::qi::eoi
                // lit("")
                // >> '{'
                // >>  int_ >> ','
                // >>  quoted_string >> ','
                // >>  quoted_string >> ','
                // >>  double_
                // >>  '}'
                ;
        }

	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> instruction_string;
	boost::spirit::qi::rule<Iterator, t_instruct(), boost::spirit::ascii::space_type> start;
};

int		main()
{
	std::list<t_instruct>						lst;
	t_instruct									tmp;
	std::string									str;
	instruction_parser<std::string::const_iterator>		g;

	while (getline(std::cin, str))
	{
		bool ret = boost::spirit::qi::phrase_parse(str.begin(), str.end(), g, boost::spirit::ascii::space, tmp);
		std::cout << tmp.name << std::endl;
	}

	return (0);
}
