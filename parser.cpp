
#include "parser.hpp"

parser::parser() : _fd(std::cin)
{}

parser::parser( const parser & src )
{
	*this = src;
}

// parser::parser( int fd ) : _fd(fd)
// {}

parser::parser( std::ifstream streamIn )
{
	this->_fd = streamIn;
}

parser::parser( std::string filename )
{
	this->_fd.open(filename);
	if (!this->_fd)
		throw parser::ParsingException();
}

parser::~parser()
{

}

parser &		parser::operator=( const parser & src )
{
	this->_instructionList = src.getInstructionList();
	this->_fd = src.getFd();
}

/** PUBLIC FUNCTION **/
void						parser::parseFile( void )
{
	std::string			line;
	bool				ret;

	while (std::getline(this->_fd, line))
	{
		if ( this->_fd == std::cin && !std::strncmp(line, ";;", 2))
			return ;
		ret = boost::spirit::qi::phrase_parse(line.begin(), line.end(), this->_grammar, this->_instructionList);
		if (!ret)
			this->_checkFailedInstruction(line); //a faire
	}
}


std::list<avm_instruct>		parser::getInstructionList( void )
{
	return ( this->_instructionList );
}

// int							parser::getFd( void )
// {
// 	return (this->_fd);
// }

std::ifstream				parser::getFd( void )
{
	return (this->_fd);
}
