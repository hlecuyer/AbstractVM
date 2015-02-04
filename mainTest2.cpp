
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <list>

class Aoperand
{
public:
	std::string		name;
};

struct		avm_instruct
{
	std::string		name;
	// Aoperand		*op;
};

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

} instructions;


BOOST_FUSION_ADAPT_STRUCT(
    avm_instruct,
    (std::string, name)
)

template <typename Iterator>
struct instruction_parser : boost::spirit::qi::grammar<Iterator, avm_instruct(), boost::spirit::ascii::space_type>
{
	instruction_parser() : instruction_parser::base_type(start)
        {
            using boost::spirit::qi::int_;
            using boost::spirit::qi::lit;
            using boost::spirit::qi::double_;
            using boost::spirit::qi::lexeme;
            using boost::spirit::ascii::char_;

            instruction_string %= boost::spirit::qi::lexeme[instructions];

            start %=
				instruction_string
				>> boost::spirit::qi::eoi
                // lit("test")
                // >> '{'
                // >>  int_ >> ','
                // // >>  quoted_string >> ','
                // // >>  quoted_string >> ','
                // >>  double_
                // >>  '}'
                ;
        }

	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> instruction_string;
	boost::spirit::qi::rule<Iterator, avm_instruct(), boost::spirit::ascii::space_type> start;
};

int		main()
{
	// std::list<avm_instruct>						lst;
	avm_instruct								tmp;
	std::string									str;
	std::list<std::string>						lstStr;
	bool										ret = false;
	instruction_parser<std::string::iterator>		g;

	// instruction_string %= boost::spirit::qi::lexeme[ instructions ];

	while (getline(std::cin, str))
	{
		bool ret = boost::spirit::qi::phrase_parse(str.begin(), str.end(), g, boost::spirit::ascii::space, tmp);
		// bool ret = boost::spirit::qi::phrase_parse(str.begin(), str.end(), '(' >> boost::spirit::qi::int_ >> ')', boost::spirit::ascii::space, lstStr);
		if (ret)
			std::cout << "okokokokokokokokokok" << std::endl;
		// std::cout << tmp.name << std::endl;
		for (std::list<std::string>::iterator it = lstStr.begin() ; it != lstStr.end(); it++)
			std::cout << *it << std::endl;
	}

	return (0);
}
	// boost::spirit::qi::rule<std::string::iterator, std::string(), boost::spirit::ascii::space_type> instruction_string;
	// instruction_string = '(' >> boost::spirit::qi::int_ >> ')';
	// 	bool ret = boost::spirit::qi::phrase_parse(str.begin(), str.end(), instruction_string, boost::spirit::ascii::space);
