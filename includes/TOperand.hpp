
#ifndef TOPERAND_HPP
# define TOPERAND_HPP

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <stdexcept>
#include <typeinfo>
#include "eOperandType.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"
// #include "VirtualMachine.hpp"

// class VirtualMachine;
class OperandFactory;

template <typename T>
class TOperand : public IOperand
{
private:
	T					_value;
	eOperandType 		_type;
	std::string			_strValue;
	OperandFactory		_operandFactory;

	TOperand();
	eOperandType		_findType( void );
	template <typename C>
	IOperand const *	_addOperand( IOperand const & rhs ) const;

public:
	TOperand(std::string value);
	TOperand(const TOperand & );
	TOperand& operator=(TOperand const &);
	~TOperand();

	int getPrecision( void ) const;
	eOperandType getType( void ) const;
	IOperand const * operator+( IOperand const & rhs ) const;
	IOperand const * operator-( IOperand const & rhs ) const;
	IOperand const * operator*( IOperand const & rhs ) const;
	IOperand const * operator/( IOperand const & rhs ) const;
	IOperand const * operator%( IOperand const & rhs ) const;
	std::string const & toString( void ) const;

};

template<typename T, typename C>
IOperand const *	TOperand<T>::_addOperand( IOperand const & rhs ) const
{
	IOperand *		newOp;
	std::string		ret;
	eOperandType	type;

	if (this->getPrecision() < rhs.getPrecision())
	{
		C		newVal;
		C		result;

		newVal = boost::numeric_cast<C>(this->_value);//VERIFIER EXCEPTION
		result = newVal + rhs._value;
		ret = boost::lexical_cast<std::string>(result);
		type = rhs.getType();
	}
	else
	{
		T		newVal;
		T		result;

		newVal = boost::numeric_cast<C>(rhs._value);//VERIFIER EXCEPTION
		result = this->_value + newVal;
		ret = boost::lexical_cast<std::string>(result);
		type = this->getType();
	}
	return (this->_operandFactory.createOperand(type, ret));
}

template <typename T>
TOperand<T>::TOperand(std::string value) : _strValue(value)
{
	this->_type = this->_findType();
	// this->_type = TOperand::_findType();
	// this->_type = TOperand::_findType<T>();
	try
	{
		this->_value = boost::numeric_cast<T>(boost::lexical_cast<double>(value));
	}
	catch ( boost::numeric::positive_overflow & e)
	{
		std::cout << "AbstractVM: int8: " << e.what() << std::endl;//MODFIER
		std::exit(-1);
	}
	catch ( boost::numeric::negative_overflow & e)
	{
		std::cout << "AbstractVM: int8: " << e.what() << std::endl;//MODFIER
		std::exit(-1);
	}
	catch ( boost::bad_lexical_cast const & e)
	{
		std::cout << "AbstractVM: int8: " << e.what() <<  std::endl;//MODFIER
		std::exit(-1);
	}
}

template <typename T>
TOperand<T>::TOperand(const TOperand & src)
{
	*this = src;
}

template <typename T>
TOperand<T> & TOperand<T>::operator=(TOperand<T> const & src)
{
	if (this != &src)
	{
		this->_value = src._value;
	}
	return (*this);
}

template <typename T>
TOperand<T>::~TOperand()
{
	return ;
}

template <typename T>
int			TOperand<T>::getPrecision( void ) const
{
	return (static_cast<int>(this->_type));
}

template <typename T>
eOperandType TOperand<T>::getType( void ) const
{
	return (this->_type);
}

template <typename T>
std::string const & TOperand<T>::toString( void ) const
{
	return (this->_strValue);
}

template <typename T>
IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const
{
	switch (rhs.getType())
	{
	case eOperandType::int8 :
		this->_addOperand<int8_t>(rhs);
	// case eOperandType::int8 : std::cout << "INT 8 !!!!!" << std::endl;
		break ;
	case eOperandType::int16 :
		this->_addOperand<int16_t>(rhs);
	// case eOperandType::int16 : std::cout << "INT 16 !!!!!" << std::endl;
		break ;
	case eOperandType::int32 :
		this->_addOperand<int32_t>(rhs);
	// case eOperandType::int32 : std::cout << "INT 32 !!!!!" << std::endl;
		break ;
	case eOperandType::floatt :
		std::cout << "INT 32 !!!!!" << std::endl;
		break ;
	case eOperandType::doublee :
		std::cout << "INT 32 !!!!!" << std::endl;
		break ;
	// default: std::cout "FAIL !!!!" << std::endl;
	// 	break ;
	}

	(void)rhs;
	return this;
}

template <typename T>
IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

template <typename T>
IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

template <typename T>
IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

template <typename T>
IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

template <typename T>
eOperandType	TOperand<T>::_findType( void )
{
	if (typeid(T) == typeid(int8_t))
		return eOperandType::int8;
	else if (typeid(T) == typeid(int16_t))
		return eOperandType::int16;
	else if (typeid(T) == typeid(int32_t))
		return eOperandType::int32;
	else if (typeid(T) == typeid(float))
		return eOperandType::floatt;

	return eOperandType::doublee;
}

#endif // ** TOPERAND_HPP ** //
