#include "Int8.hpp"

Int8::Int8(std::string value) : _strValue(value)
{
	int checkVal;

	try
	{
		checkVal = boost::lexical_cast<int>(value);
	}
	catch ( boost::bad_lexical_cast const& )
	{

		std::cout << "AbstractVM: bad cast" << std::endl;
	}
	try
	{
		validateVal(checkVal);
		this->_value = static_cast<signed char>(checkVal);
	}
	catch (std::overflow_error e)
	{
		std::cout << e.what() << std::endl;
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
	std::cout << "je suis int8 : " << static_cast<int>(this->_value)  << std::endl;
	return this->_strValue;
}

void	 Int8::validateVal(int const & val) const
{
	if (!val)
		throw new std::domain_error("Int8");
	else if (val < -128)
		throw new std::underflow_error("Int8");
	else if (val > 127)
		throw new std::overflow_error("Int8");
}
