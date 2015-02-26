#include "Double.hpp"

Double::Double(std::string value) : _strValue(value)
{
	try
	{
		this->_value = boost::lexical_cast<double>(value);
	}
	catch ( boost::bad_lexical_cast const & e)
	{
		std::cout << "AbstractVM: double: " << e.what() << std::endl;
		exit(-1);
	}
	this->_type = eOperandType::doublee;
}

Double::Double( const Double & src)
{
	*this = src;
}

Double& Double::operator=(const Double & src)
{
	if (this != &src)
	{
		this->_value = src._value;
	}
	return (*this);
}

Double::~Double()
{
	return ;
}

int Double::getPrecision( void ) const
{
	return (static_cast<int>(this->_type));
}

eOperandType Double::getType( void ) const
{
	return this->_type;
}

IOperand const * Double::operator+( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Double(*this);
	return ret;
}

IOperand const * Double::operator-( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Double(*this);
	return ret;
}

IOperand const * Double::operator*( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Double(*this);
	return ret;
}

IOperand const * Double::operator/( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Double(*this);
	return ret;
}

IOperand const * Double::operator%( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Double(*this);
	return ret;
}

std::string const & Double::toString( void ) const
{
	// std::cout << "je suis double" << std::endl;
	return this->_strValue;
}
