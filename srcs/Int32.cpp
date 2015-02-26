#include "Int32.hpp"

Int32::Int32(std::string value) : _strValue(value)
{
	try
	{
		this->_value = boost::numeric_cast<int32_t>(boost::lexical_cast<long>(value));
	}
	catch ( boost::numeric::positive_overflow & e)
	{
		std::cout << "AbstractVM: int32: " << e.what() << std::endl;
		std::exit(-1);
	}
	catch ( boost::numeric::negative_overflow & e)
	{
		std::cout << "AbstractVM: int32: " << e.what() << std::endl;
		std::exit(-1);
	}
	catch ( boost::bad_lexical_cast const & e)
	{
		std::cout << "AbstractVM: int32: " << e.what() <<  std::endl;
		exit(-1);
	}
	// try
	// {
	// 	this->_value = boost::lexical_cast<int>(value);;
	// }
	this->_type = eOperandType::int32;
}

Int32::Int32( const Int32 & src)
{
	*this = src;
}

Int32& Int32::operator=(const Int32 & src)
{
	if (this != &src)
	{
		this->_value = src._value;
	}
	return (*this);
}

Int32::~Int32()
{
	return ;
}

int Int32::getPrecision( void ) const
{
	return (static_cast<int>(this->_type));
}

eOperandType Int32::getType( void ) const
{
	return this->_type;
}

IOperand const * Int32::operator+( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int32(*this);
	return ret;
}

IOperand const * Int32::operator-( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int32(*this);
	return ret;
}

IOperand const * Int32::operator*( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int32(*this);
	return ret;
}

IOperand const * Int32::operator/( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int32(*this);
	return ret;
}

IOperand const * Int32::operator%( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int32(*this);
	return ret;
}

std::string const & Int32::toString( void ) const
{
	// std::cout << "je suis int32" << std::endl;
	return this->_strValue;
}
