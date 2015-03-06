
#include "parser.hpp"


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
			err = "value after token with no required value";
		else
			err = "error";
		throw Parser::ParsingException(err, _lineCount, instruction);
	}
}

void			Parser::_initRules( void )
{
	this->_commentString = boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_];
	this->_errorStringWithValue = boost::spirit::qi::lexeme[instructions] >> boost::spirit::qi::lexeme[values] >> '(' >> boost::spirit::qi::double_ >> ')' >> -(boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_]) >> boost::spirit::qi::eoi;
}

// void			Parser::_printDebug(avm_instruct instructDebug)
// {
// 	std::cout << instructDebug.name;
// 	if (instructDebug.instrType.type != "")
// 		std::cout << " [" << instructDebug.instrType.type << "] [" << instructDebug.instrType.value << "]";
// 	std::cout << std::endl;
// }


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

// void						Parser::dumpDebug( void )
// {
// 	for_each(this->_instructionList.begin(), this->_instructionList.end(), &Parser::_printDebug);
// }

Parser::ParsingException(std::string errType, const int & line, const std::string & instruction)
 : _errType(errType), _line(line), _instruction(instruction)
{

}

int 				Parser::ParsingException::getLine() const
{
	return (_line);
}

std::string 		Parser::ParsingException::getInstruction() const
{
	return (_instruction);
}

std::string 		Parser::ParsingException::getErrType() const
{
	return (_errType);
}
	
const char*					Parser::ParsingException::what() const throw()
{

	std::string ret = "AbstractVM: " << this->_errType << std::endl << "AbstractVM: error line " << this->_lineCount << " : " << this->_instruction << std::endl;
	return ret.c_str();
}
