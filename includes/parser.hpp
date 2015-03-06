


#ifndef PARSER_HPP
# define PARSER_HPP

#include "misc.hpp"
#include <string>
#include <list>
#include <stdexcept>
#include <fstream>

struct				instr_type
{
	std::string		type;
	std::string			value;
	//double			value;
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
    (std::string, value)
//    (double, value)
)


template <typename Iterator>
struct instruction_parser : boost::spirit::qi::grammar<Iterator, avm_instruct(), boost::spirit::ascii::space_type>
{
	instruction_parser() : instruction_parser::base_type(start)
        {

            instruction_string %= boost::spirit::qi::lexeme[instructions];
            type_string %= boost::spirit::qi::lexeme[values];
			comment_string %= boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_];
			value_string %= boost::spirit::qi::lexeme[*boost::spirit::ascii::char_];

            start %=
				instruction_string [boost::phoenix::ref(rf) = boost::spirit::qi::_1]
				>> -((boost::spirit::qi::eps(boost::phoenix::ref(rf) == "assert") | boost::spirit::qi::eps(boost::phoenix::ref(rf) == "push"))
					 > boost::spirit::qi::as_string[type_string] > '('
					 > boost::spirit::qi::raw[boost::spirit::qi::double_] > ')'
					 // > boost::spirit::qi::double_ > ')'
				)
				>> -comment_string
				>> boost::spirit::qi::eoi
                ;

			start.name("start_tag");

			boost::spirit::qi::on_error<boost::spirit::qi::fail>(
				start,
				std::cout << boost::phoenix::val("AbstractVM : No value after token : ") << boost::phoenix::construct<std::string>(boost::spirit::qi::_1, boost::spirit::qi::_3) << std::endl
			);
        }
	std::string		rf;

	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> instruction_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> type_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> comment_string;
	boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> value_string;
	boost::spirit::qi::rule<Iterator, avm_instruct(), boost::spirit::ascii::space_type> start;
};


class Parser
{
private :
	/** ATTRIBUTES **/
	std::istream*									_fd;
	std::list<avm_instruct>							_instructionList;
	instruction_parser<std::string::iterator>		_grammar;
	int												_lineCount;
	boost::spirit::qi::rule<std::string::iterator, std::string(), boost::spirit::ascii::space_type> _commentString;
	boost::spirit::qi::rule<std::string::iterator, std::string(), boost::spirit::ascii::space_type> _errorStringWithValue;


	/** PRIVATE FUNCTION **/
	void			_checkFailedInstruction( std::string instruction );
	void			_initRules( void );
	// void			_printDebug(avm_instruct instructDebug);

public:
	/** CANONICAL **/
	Parser();
	Parser( const Parser & src );
	Parser( std::ifstream* streamIn );
	~Parser();

	Parser &		operator=( const Parser & src );

	/** PUBLIC FUNCTION **/
	void						parseFile();

	const std::list<avm_instruct>	&	getInstructionList( void ) const;
	std::istream*				getFd( void ) const;
	// void						dumpDebug( void ); // a faire

	class ParsingException : public std::runtime_error
	{
		private:
			// ParsingException(ParsingException const &) throw();
			ParsingException const & operator=(ParsingException const &) throw();
			ParsingException() throw();
			std::string const	_errType;
			int	const			_line;
			std::string const	_instruction;

		public:
			ParsingException(std::string const & errType, int  const & line, std::string const & instruction) throw();
			~ParsingException() throw();
			virtual const char* what() const throw();
			int 		getLine() const;
			std::string getInstruction() const;
			std::string getErrType() const;

	};
};



#endif /** PARSER_HPP **/

