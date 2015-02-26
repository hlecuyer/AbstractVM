#include "Float.hpp"

Float::Float(std::string value) : _strValue(value)
{
	try
	{
		this->_value = std::stof(value);
	}
	catch ( boost::bad_lexical_cast const& )
	{
		std::cout << "AbstractVM: bad cast" << std::endl;
	}
	this->_type = eOperandType::floatt;
}

Float::Float( const Float & src)
{
	*this = src;
}

Float& Float::operator=(const Float & src)
{
	if (this != &src)
	{
		this->_value = src._value;
	}
	return (*this);
}

Float::~Float()
{
	return ;
}

int Float::getPrecision( void ) const
{
	return (static_cast<int>(this->_type));
}

eOperandType Float::getType( void ) const
{
	return this->_type;
}

IOperand const * Float::operator+( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Float(*this);
	return ret;
}

IOperand const * Float::operator-( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Float(*this);
	return ret;
}

IOperand const * Float::operator*( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Float(*this);
	return ret;
}

IOperand const * Float::operator/( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Float(*this);
	return ret;
}

IOperand const * Float::operator%( IOperand const & rhs ) const
{
	if (this != &rhs){

	}
	IOperand *ret = new Float(*this);
	return ret;
}

std::string const & Float::toString( void ) const
{
	std::cout << "je suis float" << std::endl;
	return this->_strValue;
}
