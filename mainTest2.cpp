
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <iostream>
#include <string>
#include <list>

class Aoperand
{
public:
	std::string		name;
};

struct		instr_type
{
	std::string		type;
	double			nb;
};

struct		avm_instruct
{
	std::string		name;
	instr_type		tp;
	// std::string		type;
	// double			nb;
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

// ici struct pour separer les deux types d'instructions, celles avec valeur et celles sans
struct instructionsVal_ : boost::spirit::qi::symbols<char, std::string>
{
	instructionsVal_()
		{
            add
                ("push"   , "push")
                ("assert"   , "assert")
				;
		}

} instructionsVal;

struct values_ : boost::spirit::qi::symbols<char, std::string>
{
	values_()
		{
            add
                ("int8"    , "int8")
                ("int16"   , "int16")
                ("int32"  , "int32")
                ("float"   , "float")
                ("double"    , "double")
				;
		}

} values;


BOOST_FUSION_ADAPT_STRUCT(
    avm_instruct,
    (std::string, name)
	(instr_type, tp)
    // (std::string, type)
    // (double, nb)
)

BOOST_FUSION_ADAPT_STRUCT(
    instr_type,
    (std::string, type)
    (double, nb)
)

template <typename Iterator>
struct instruction_parser : boost::spirit::qi::grammar<Iterator, avm_instruct(), boost::spirit::ascii::space_type>
{
	//toutes les lignes finissant par // ne servent a rien, c'est pour preparer les deux types d'instruction, celles
	//suivies de valeurs et celles qui ne le sont pas
	instruction_parser() : instruction_parser::base_type(start)
        {

            instruction_string %= boost::spirit::qi::lexeme[instructions];
            instructionVal_string %= boost::spirit::qi::lexeme[instructionsVal];//
            type_string %= boost::spirit::qi::lexeme[values];
			comment_string %= boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_];

			instr %= instruction_string;//
			instrVal %= instructionVal_string >> type_string >> '(' >> boost::spirit::qi::double_ >> ')';//

			// start = instr | instrVal >> -comment_string >> boost::spirit::qi::eoi;//
			// start = instruction_string >> -comment_string >> boost::spirit::qi::eoi;//

            start %=
				instruction_string [boost::phoenix::ref(rf) = boost::spirit::qi::_1]
				>> -(
					(boost::spirit::qi::eps(boost::phoenix::ref(rf) == "assert") | boost::spirit::qi::eps(boost::phoenix::ref(rf) == "push"))
					> type_string > '('
					> boost::spirit::qi::double_ > ')'
				)
				>> -comment_string
				>> boost::spirit::qi::eoi
                ;

            // start %=
			// 	instruction_string
			// 	>> -(type_string >> '(' >> boost::spirit::qi::double_ >> ')')
			// 	>> -comment_string
			// 	>> boost::spirit::qi::eoi
            //     ;
        }
	std::string		rf;

	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> instruction_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> instructionVal_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> type_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> comment_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> instr;//
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> instrVal;//
	boost::spirit::qi::rule<Iterator, avm_instruct(), boost::spirit::ascii::space_type> start;
};

int		main()
{
	std::list<avm_instruct>						lst;
	avm_instruct								tmp;
	std::string									str;
	std::list<std::string>						lstStr;
	bool										ret = false;
	instruction_parser<std::string::iterator>		g;

	// instruction_string %= boost::spirit::qi::lexeme[ instructions ];

	while (getline(std::cin, str))
	{
		bool ret = boost::spirit::qi::phrase_parse(str.begin(), str.end(), g, boost::spirit::ascii::space, lst);
		// bool ret = boost::spirit::qi::phrase_parse(str.begin(), str.end(), g, boost::spirit::ascii::space, tmp);
		// bool ret = boost::spirit::qi::phrase_parse(str.begin(), str.end(), '(' >> boost::spirit::qi::int_ >> ')', boost::spirit::ascii::space, lstStr);
		if (ret)
			std::cout << "parsing ok" << std::endl;
		else
			std::cout << "parsing failed" << std::endl;
		// std::cout << tmp.name << std::endl;
		std::cout << "Current list : " << std::endl;
		for (std::list<avm_instruct>::iterator it = lst.begin() ; it != lst.end(); it++)
			std::cout << (*it).name << "[" << (*it).tp.type << "," << (*it).tp.nb << "]" << std::endl;
		std::cout << "*********************************************" << std::endl;
	}

	return (0);
}
	// boost::spirit::qi::rule<std::string::iterator, std::string(), boost::spirit::ascii::space_type> instruction_string;
	// instruction_string = '(' >> boost::spirit::qi::int_ >> ')';
	// 	bool ret = boost::spirit::qi::phrase_parse(str.begin(), str.end(), instruction_string, boost::spirit::ascii::space);
