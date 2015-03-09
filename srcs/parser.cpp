
#include "parser.hpp"
#include <boost/lexical_cast.hpp>


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
		if (boost::spirit::qi::phrase_parse(instruction.begin(), instruction.end(), this->_errorStringWithValue, boost::spirit::ascii::space))
			err = "Value after token with no required value";
		else
			err = "Parsing error";
		throw Parser::ParsingException(err, _lineCount, instruction);
	}
}

void			Parser::_initRules( void )
{
	this->_commentString = boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_];
	this->_errorStringWithValue = boost::spirit::qi::lexeme[instructions] >> boost::spirit::qi::lexeme[values] >> '(' >> boost::spirit::qi::double_ >> ')' >> -(boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_]) >> boost::spirit::qi::eoi;
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
		std::cout << "Getline : " << line << std::endl; //DEBUG
		if (line == "")
			continue ;
		if ( this->_fd == &std::cin && !std::strncmp(line.c_str(), ";;", 2))
			return ;
		ret = boost::spirit::qi::phrase_parse(line.begin(), line.end(), this->_grammar, boost::spirit::ascii::space, this->_instructionList);
		if (!ret)
			this->_checkFailedInstruction(line);
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

Parser::ParsingException::ParsingException(std::string const & errType, int const & online, std::string const & instruction) throw()
	: std::runtime_error(errType), _errType(errType), _line(online), _instruction(instruction)
{

}

int 				Parser::ParsingException::getLine() const
{
	return (this->_line);
}

std::string 		Parser::ParsingException::getInstruction() const
{
	return (this->_instruction);
}

std::string 		Parser::ParsingException::getErrType() const
{
	return (this->_errType);
}

const char*					Parser::ParsingException::what() const throw()
{
	std::string test = getErrType();
	std::string ret = "AbstractVM: " + test + "\n" + "AbstractVM: error line " + boost::lexical_cast<std::string>(this->_line) + " : " + this->_instruction + "\n";
	return ret.c_str();
}

Parser::ParsingException::~ParsingException() throw()
{
	return ;
}
