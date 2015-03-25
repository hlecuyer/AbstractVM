


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
				)
				>> -comment_string
				>> boost::spirit::qi::eoi
                ;

			start.name("start_tag");
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
	std::list<std::string>							_exceptionList;
	instruction_parser<std::string::iterator>		_grammar;
	int												_lineCount;
	bool											_parsingSuccess;
	boost::spirit::qi::rule<std::string::iterator, std::string(), boost::spirit::ascii::space_type> _commentString;
	boost::spirit::qi::rule<std::string::iterator, std::string(), boost::spirit::ascii::space_type> _errorStringWithValue;


	/** PRIVATE FUNCTION **/
	void			_checkFailedInstruction( std::string instruction );
	void			_initRules( void );
	void			_addException(std::string error, int line, std::string instruction);

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

	class ParsingException : public std::runtime_error
	{
		private:
			ParsingException const & operator=(ParsingException const &) throw();
			ParsingException() throw();
		std::list<std::string> const & _errorList;

	public:
		ParsingException(std::list<std::string> const & errorList ) throw();
		~ParsingException() throw();
			virtual const char* 		what() const throw();

	};
};



#endif /** PARSER_HPP **/
