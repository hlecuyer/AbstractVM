#include "Int8.hpp"

Int8::Int8(std::string value) : _strValue(value)
{
	try
	{
		this->_value = boost::lexical_cast<char>(value);
	}
	catch ( boost::bad_lexical_cast const& )
	{
		std::cout << "AbstractVM: bad cast" << std::endl;
	}
	this->_type = eOperandType::int8;
}

Int8::Int8(const Int8 & src)
{
	*this = src;
}

Int8& Int8::operator=(const Int8 & src)
{
	if (this != &src)
	{
		this->_value = src._value;
	}
	return (*this);
}

Int8::~Int8()
{
	return ;
}

int Int8::getPrecision( void ) const
{
	return (static_cast<int>(this->_type));
}

eOperandType Int8::getType( void ) const
{
	return this->_type;
}

IOperand const * Int8::operator+( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int8(*this);
	return ret;
}

IOperand const * Int8::operator-( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int8(*this);
	return ret;
}

IOperand const * Int8::operator*( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int8(*this);
	return ret;

}

IOperand const * Int8::operator/( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int8(*this);
	return ret;

}

IOperand const * Int8::operator%( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Int8(*this);
	return ret;

}

std::string const & Int8::toString( void ) const
{
	std::cout << "je suis int8" << std::endl;
	return this->_strValue;
}
