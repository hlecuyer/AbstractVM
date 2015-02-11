
#include "parser.hpp"


void			Parser::_checkFailedInstruction( std::string instruction )
{
	if (boost::spirit::qi::phrase_parse(instruction.begin(), instruction.end(), boost::spirit::qi::lexeme[';' >> *boost::spirit::ascii::char_], boost::spirit::ascii::space))
		return ;
	else
		throw Parser::ParsingException();
}


Parser::Parser( void )
{
	this->_fd = &(std::cin);
}

Parser::Parser( const Parser & src )
{
	*this = src;
}

// Parser::Parser( int fd ) : _fd(fd)
// {}

Parser::Parser( std::ifstream* streamIn )
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
		if ( this->_fd == &std::cin && !std::strncmp(line.c_str(), ";;", 2))
			return ;
		// ret = boost::spirit::qi::phrase_parse(line.begin(), line.end(), grammar, boost::spirit::ascii::space, this->_instructionList);
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
