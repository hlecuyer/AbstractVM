
#include "parser.hpp"


// ** PRIVATE FUNCTION ** //

void			Parser::_checkFailedInstruction( std::string instruction )
{
	// std::cout << "CheckFailedInstruction : " << instruction << std::endl; //DEBUG
	if (boost::spirit::qi::phrase_parse(instruction.begin(), instruction.end(), boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_], boost::spirit::ascii::space))
	{
		// std::cout << "return comment or empty line" << std::endl;
		return ;
	}
	else
	{
		if (boost::spirit::qi::phrase_parse(instruction.begin(), instruction.end(), instructions >> boost::spirit::qi::lexeme[values] >> '(' >> boost::spirit::qi::double_ >> ')' >> -(boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_]) >> boost::spirit::qi::eoi, boost::spirit::ascii::space))
			std::cout << "AbstractVM: value after token with no required value" << std::endl;
		std::cout << "AbstractVM: error line " << this->_lineCount << " : " << instruction << std::endl;
		throw Parser::ParsingException();
	}
		// throw std::exception();
}


// ** CANONICAL ** //

Parser::Parser( void ) : _lineCount(0)
{
	this->_fd = &(std::cin);
}

Parser::Parser( const Parser & src ) : _lineCount(0)
{
	*this = src;
}

// Parser::Parser( int fd ) : _fd(fd)
// {}

Parser::Parser( std::ifstream* streamIn ) : _lineCount(0)
{
	this->_fd = streamIn;
}

// Parser::Parser( std::string filename )
// {
// 	this->_tempFd.open(filename, std::ifstream::in);
// 	this->_fd = &(this->_tempFd);
// 	if ((this->_fd)->is_open())
// 		throw Parser::ParsingException();
// 	// this->_fd = new std::ifstream(filename);
// 	// if (!static_cast<std::ifstream*>(this->_fd)->is_open())
// 	// 	throw Parser::ParsingException();
// }

Parser::~Parser()
{
//	if (fd != std::cin)
//		this->_fd.close();
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
	// instruction_parser<std::string::iterator>		grammar;

	while (std::getline(*this->_fd, line))
	{
		this->_lineCount++;
		std::cout << "Getline : " << line << std::endl; //DEBUG
		if ( this->_fd == &std::cin && !std::strncmp(line.c_str(), ";;", 2))
			return ;
		// ret = boost::spirit::qi::phrase_parse(line.begin(), line.end(), grammar, boost::spirit::ascii::space, this->_instructionList);
		if (line == "")
			continue ;
		ret = boost::spirit::qi::phrase_parse(line.begin(), line.end(), this->_grammar, boost::spirit::ascii::space, this->_instructionList);
		if (!ret)
			this->_checkFailedInstruction(line); //a faire
	}
}


std::list<avm_instruct>		Parser::getInstructionList( void ) const
{
	return ( this->_instructionList );
}

// int							Parser::getFd( void )
// {
// 	return (this->_fd);
// }

std::istream*				Parser::getFd( void ) const
{
	return (this->_fd);
}

const char*					Parser::ParsingException::what() const throw()
{
	return "AbstractVM: Parsing error";
}
