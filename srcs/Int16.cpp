#include "Int16.hpp"

Int16::Int16(std::string value) : _strValue(value)
{
	try
	{
		this->_value = boost::numeric_cast<int16_t>(boost::lexical_cast<int>(value));
	}
	catch ( boost::numeric::positive_overflow & e)
	{
		std::cout << "AbstractVM: int16: " << e.what() << std::endl;
		std::exit(-1);
	}
	catch ( boost::numeric::negative_overflow & e)
	{
		std::cout << "AbstractVM: int16: " << e.what() << std::endl;
		std::exit(-1);
	}
	catch ( boost::bad_lexical_cast const & e)
	{
		std::cout << "AbstractVM: int16: " << e.what() <<  std::endl;
		std::exit(-1);
	}
	// try
	// {
	// 	this->_value = static_cast<signed short int>(boost::lexical_cast<int>(value));
	// }
	// catch ( boost::bad_lexical_cast const& )
	// {
	// 	std::cout << "AbstractVM: bad cast" << std::endl;
	// }
	this->_type = eOperandType::int16;
}

Int16::Int16( const Int16 & src)
{
	*this = src;
}

Int16& Int16::operator=(const Int16 & src)
{
	if (this != &src)
	{
		this->_value = src._value;
	}
	return (*this);
}

Int16::~Int16()
{
	return ;
}

int Int16::getPrecision( void ) const
{
	return (static_cast<int>(this->_type));
}

eOperandType Int16::getType( void ) const
{
	return this->_type;
}

IOperand const * Int16::operator+( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int16(*this);
	return ret;
}

IOperand const * Int16::operator-( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int16(*this);
	return ret;
}

IOperand const * Int16::operator*( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int16(*this);
	return ret;
}

IOperand const * Int16::operator/( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int16(*this);
	return ret;
}

IOperand const * Int16::operator%( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int16(*this);
	return ret;
}

std::string const & Int16::toString( void ) const
{
	// std::cout << "je suis Int16 : " << this->_value  << std::endl;
	return this->_strValue;
}
