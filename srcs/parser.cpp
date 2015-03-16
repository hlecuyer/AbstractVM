
#include "parser.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/spirit/include/qi_expect.hpp>

// ** PRIVATE FUNCTION ** //

void			Parser::_checkFailedInstruction( std::string instruction )
{
	if (boost::spirit::qi::phrase_parse(instruction.begin(), instruction.end(), this->_commentString, boost::spirit::ascii::space))
	{
		return ;
	}
	else
	{
		std::string err;
		bool boole;
		boole = boost::spirit::qi::phrase_parse(instruction.begin(), instruction.end(), this->_errorStringWithValue, boost::spirit::ascii::space);
		if (boole)
			err = "value after token with no required value";
		else
			err = "unknown instruction";
		this->_addException(err, this->_lineCount, instruction);
	}
}

void			Parser::_initRules( void )
{
	this->_parsingSuccess = true;

	this->_commentString = boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_];
	this->_errorStringWithValue = boost::spirit::qi::lexeme[instructions] >> boost::spirit::qi::lexeme[values] >> '(' >> boost::spirit::qi::double_ >> ')' >> -(boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_]) >> boost::spirit::qi::eoi;
}

void			Parser::_addException( std::string error, int line, std::string instruction )
{
	std::string		excep;

	if (this->_parsingSuccess)
		this->_parsingSuccess = false;
	excep = "Parser: parsing error line " + std::to_string(line) + ": \"" + instruction + "\" : " + error;
	this->_exceptionList.push_back(excep);
}


// ** CANONICAL ** //

Parser::Parser( void ) : _lineCount(0)
{
	this->_fd = &(std::cin);
	this->_initRules();
}

Parser::Parser( const Parser & src ) : _lineCount(0)
{
	*this = src;
	this->_initRules();
}

Parser::Parser( std::ifstream* streamIn ) : _lineCount(0)
{
	this->_fd = streamIn;
	this->_initRules();
}

Parser::~Parser()
{
	return ;
}

Parser &					Parser::operator=( const Parser & src )
{
	this->_instructionList = src.getInstructionList();
	this->_fd = src.getFd();
	return *this;
}

/** PUBLIC FUNCTION **/
void						Parser::parseFile( void )
{
	std::string			line;
	bool				ret;

	while (std::getline(*this->_fd, line))
	{
		this->_lineCount++;
		if (line == "")
			continue ;
		if ( this->_fd == &std::cin && !std::strncmp(line.c_str(), ";;", 2))
			break ;
		try
		{

				ret = boost::spirit::qi::phrase_parse(line.begin(), line.end(), this->_grammar, boost::spirit::ascii::space, this->_instructionList);

			if (!ret)
				this->_checkFailedInstruction(line);
		}
		catch (boost::spirit::qi::expectation_failure<std::string::iterator> const& x)
		{

			std::string		error;

			error = std::string("no value after instruction with required value") + "\nLine " + std::to_string(this->_lineCount) + " error near: " + std::string(x.first, x.last);
			this->_addException(error, this->_lineCount, line);
		}
	}
	if (!this->_parsingSuccess)
	{
		throw Parser::ParsingException(this->_exceptionList);

	}
}


const std::list<avm_instruct> &		Parser::getInstructionList( void ) const
{
	return ( this->_instructionList );
}

std::istream*				Parser::getFd( void ) const
{
	return (this->_fd);
}

// *************** //
// ** EXCEPTION ** //
// *************** //

Parser::ParsingException::ParsingException(std::list<std::string> const & errorList) throw()
	: std::runtime_error("bla"), _errorList(errorList)
{

}

const char*					Parser::ParsingException::what() const throw()
{
	std::string								ret;
	std::list<std::string>::const_iterator	it;
	std::list<std::string>::const_iterator	ite = this->_errorList.cend();

	ret = "Parsing failed with following errors :\n";

	for (it  = this->_errorList.cbegin(); it != ite; it++ )
	{
		ret += *it;
		if (*it != this->_errorList.back())
			ret += "\n";
	}
	return ret.c_str();
}

Parser::ParsingException::~ParsingException() throw()
{
	return ;
}

