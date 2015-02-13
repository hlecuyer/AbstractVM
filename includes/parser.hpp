
#ifndef PARSER_HPP
# define PARSER_HPP

#include "misc.hpp"
#include <string>
#include <list>
#include <exception>
#include <fstream>

struct				instr_type
{
	std::string		type;
	double			value;
};

struct					avm_instruct
{
	std::string			name;
	instr_type			instrType;
};


static struct instructions_ : boost::spirit::qi::symbols<char, std::string>
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

static struct values_ : boost::spirit::qi::symbols<char, std::string>
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
	(instr_type, instrType)
)

BOOST_FUSION_ADAPT_STRUCT(
    instr_type,
    (std::string, type)
    (double, value)
)


template <typename Iterator>
struct instruction_parser : boost::spirit::qi::grammar<Iterator, avm_instruct(), boost::spirit::ascii::space_type>
{
	instruction_parser() : instruction_parser::base_type(start)
        {

            instruction_string %= boost::spirit::qi::lexeme[instructions];
            type_string %= boost::spirit::qi::lexeme[values];
			comment_string %= boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_];

			/*
			** ca marche presque ca, mais ne lance pas d'exeption sur intructionSansValeur > valeur
			** par contre le parsing fail, comme sur les commentaires
			*/
            start %=
				instruction_string [boost::phoenix::ref(rf) = boost::spirit::qi::_1]
				>> -((boost::spirit::qi::eps(boost::phoenix::ref(rf) == "assert") | boost::spirit::qi::eps(boost::phoenix::ref(rf) == "push"))
					 > type_string > '('
					 > boost::spirit::qi::double_ > ')'
				)
				>> -comment_string
				>> boost::spirit::qi::eoi
                ;

			/*
			** debut de gestion des erreurs, recupere lexception mais ne se declenche pas sur un simple fail
			*/
			boost::spirit::qi::on_error<boost::spirit::qi::fail>(
				start,
				std::cout << boost::phoenix::val("AbstractVM : No value after token : ") << boost::phoenix::val(rf) << std::endl
				//throw std::exception()
				// throw Parser::ParsingException()
				// std::cout << boost::phoenix::val("je suis la !!") << std::endl
			);
        }
	std::string		rf;

	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> instruction_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> instructionVal_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> type_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> comment_string;
	boost::spirit::qi::rule<Iterator, avm_instruct(), boost::spirit::ascii::space_type> start;
};


class Parser
{
private :
	/** ATTRIBUTES **/
	// int							_fd;
	std::istream*									_fd;
	// std::ifstream									_tempFd;
	std::list<avm_instruct>							_instructionList;
	instruction_parser<std::string::iterator>		_grammar;

	/** PRIVATE FUNCTION **/
	void			_checkFailedInstruction( std::string instruction ); //a faire

public:
	/** CANONICAL **/
	Parser();
	Parser( const Parser & src );
	// Parser( int fd );
	Parser( std::ifstream* streamIn );
	// Parser( std::string filename );
	~Parser();

	Parser &		operator=( const Parser & src );

	/** PUBLIC FUNCTION **/
	void						parseFile();

	std::list<avm_instruct>		getInstructionList( void ) const;
	std::istream*				getFd( void ) const;
	// void						dumpDebug( void ); // a faire

	// class ParsingException : public std::exception
	// {
	// 	public :
	// 		// ParsingException( void ) throw();
	// 		// ParsingException( GradeTooHighException const & src ) throw();
	// 		// ~ParsingException( void ) throw();
	// 		virtual const char* what() const throw();
	// 	// private :
	// 	// 	ParsingException &operator=( ParsingException const & src );
	// };
};



#endif /** PARSER_HPP **/

