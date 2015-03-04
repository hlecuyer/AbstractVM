
#ifndef TOPERAND_HPP
# define TOPERAND_HPP

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <stdexcept>
#include <typeinfo>
#include <limits>
#include <cmath>
#include "eOperandType.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"

enum operationType {
	addOp,
	subOp,
	mulOp,
	divOp,
	modOp
};

template <typename T>
class TOperand : public IOperand
{
private:
	T					_value;
	eOperandType 		_type;
	std::string			_strValue;
	std::string			_typeStr;
	OperandFactory		_operandFactory;

	TOperand();
	void		_findType( void );

	IOperand const *	_castOperand( IOperand const & rhs, operationType operation) const ;

	template <typename C>
	IOperand const *	_genericOperation( TOperand<C> const * rhs, operationType operation ) const ;

	template <typename C>
	C					_operatorsSwitch(C a, C b, operationType operation) const ;

	template <typename Q>
	Q _addOp(Q a, Q b) const ;

	template <typename Q>
	Q _subOp(Q a, Q b) const ;

	template <typename Q>
	Q _mulOp(Q a, Q b) const ;

	template <typename Q>
	Q _divOp(Q a, Q b) const ;

	template <typename Q>
	Q _modOp(Q a, Q b) const ;

public:
	TOperand(std::string value);
	TOperand(const TOperand & );
	TOperand& operator=(TOperand const &);
	~TOperand();

	int				getPrecision( void ) const;
	T				getValue( void ) const;
	eOperandType	getType( void ) const;
	IOperand const * operator+( IOperand const & rhs ) const;
	IOperand const * operator-( IOperand const & rhs ) const;
	IOperand const * operator*( IOperand const & rhs ) const;
	IOperand const * operator/( IOperand const & rhs ) const;
	IOperand const * operator%( IOperand const & rhs ) const;
	std::string const & toString( void ) const;

};

// template <typename T, typename C>
template <typename T>
template <typename C>
C		TOperand<T>::_operatorsSwitch(C a, C b, operationType operation) const
{
	switch (operation)
	{
	case operationType::addOp :
		return this->_addOp<C>(a, b);
		break ;
	case operationType::subOp :
		return this->_subOp<C>(a, b);
		break ;
	case operationType::mulOp :
		return this->_mulOp<C>(a, b);
		break ;
	case operationType::divOp :
		return this->_divOp<C>(a, b);
		break ;
	case operationType::modOp :
		return this->_modOp<C>(a, b);
		break ;
	}

	return 0;
}


template <typename T>
template <typename Q>
Q TOperand<T>::_addOp (Q a, Q b) const
{
	if (b > 0 && a > std::numeric_limits<Q>::max() - b)
		std::cout << "Overflow Exeption blabla" << std::endl;
	if (b < 0 && a < std::numeric_limits<Q>::lowest() - b)
		std::cout << "Underflow Exeption" << std::endl;
	return (a + b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_subOp (Q a, Q b) const
{
	if (b > 0 && a > std::numeric_limits<Q>::max() + b)
		std::cout << "Overflow Exeption" << std::endl;
	if (b < 0 && a < std::numeric_limits<Q>::lowest() + b)
		std::cout << "Underflow Exeption" << std::endl;
	return (a - b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_mulOp (Q a, Q b) const
{
	if (((a > 0 && b > 0) || (a < 0 && b < 0)) && a > std::numeric_limits<Q>::max() / b)
		std::cout << "Overflow Exeption" << std::endl;
	if (((a > 0 && b < 0) || (a < 0 && b > 0)) && a < std::numeric_limits<Q>::lowest() / b)
		std::cout << "Underflow Exeption" << std::endl;
	return (a * b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_divOp (Q a, Q b) const
{
	if (b == 0)
		std::cout << "Can't divide by 0 Exeption" << std::endl;
	if (((a > 0 && b > 0) || (a < 0 && b < 0)) && a > std::numeric_limits<Q>::max() * b)
		std::cout << "Overflow Exeption" << std::endl;
	if (((a > 0 && b < 0) || (a < 0 && b > 0)) && a < std::numeric_limits<Q>::lowest() * b)
		std::cout << "Underflow Exeption" << std::endl;
	return (a / b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_modOp (Q a, Q b) const
{
	if (!std::is_integral<Q>::value)
	 	return (fmod(a, b));
	else {
		int _a = static_cast<int>(a);
		int _b = static_cast<int>(b);
		return (_a % _b);
	}
}

template <typename T>
template <typename C>
IOperand const *	TOperand<T>::_genericOperation( TOperand<C> const * rhs, operationType operation ) const
{
	std::string		ret;
	eOperandType	type;

	if (this->getPrecision() < rhs->getPrecision())
	{
		C		newVal;
		C		result;

		newVal = boost::numeric_cast<C>(this->_value);

		result = this->_operatorsSwitch<C> (newVal, rhs->getValue(), operation);
		ret = boost::lexical_cast<std::string>(result);
		type = rhs->getType();
	}
	else
	{
		T		newVal;
		T		result;

		newVal = boost::numeric_cast<T>(rhs->getValue());
		result = this->_operatorsSwitch<T> (this->_value, newVal, operation);
		ret = boost::lexical_cast<std::string>(result);
		type = this->getType();
	}
	return (this->_operandFactory.createOperand(type, ret));
}

template <typename T>
TOperand<T>::TOperand(std::string value) : _strValue(value)
{
	this->_findType();

	try
	{
		this->_value = boost::numeric_cast<T>(boost::lexical_cast<double>(value));
	}
	catch ( boost::numeric::positive_overflow & e)
	{
		std::cout << "AbstractVM: " << this->_typeStr << ": " << e.what() << std::endl;
		std::exit(-1);
	}
	catch ( boost::numeric::negative_overflow & e)
	{
		std::cout << "AbstractVM: " << this->_typeStr << ": " << e.what() << std::endl;
		std::exit(-1);
	}
	catch ( boost::bad_lexical_cast const & e)
	{
		std::cout << "AbstractVM: " << this->_typeStr << ": " << e.what() <<  std::endl;
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
T			TOperand<T>::getValue( void ) const
{
	return (this->_value);
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
IOperand const * TOperand<T>::_castOperand( IOperand const & rhs, operationType operation) const
{
	switch (rhs.getType())
	{
	case eOperandType::int8 :
		return (this->_genericOperation<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs), operation ));
		break ;
	case eOperandType::int16 :
		return (this->_genericOperation<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs), operation ));
		break ;
	case eOperandType::int32 :
		return (this->_genericOperation<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs), operation ));
		break ;
	case eOperandType::floatt :
		return (this->_genericOperation<float>(  reinterpret_cast< TOperand<float> const * >(&rhs), operation ));
		break ;
	case eOperandType::doublee :
		return (this->_genericOperation<double>(  reinterpret_cast< TOperand<double> const * >(&rhs), operation ));
		break ;
	}

	return this;
}

template <typename T>
IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const
{
	return (this->_castOperand(rhs, operationType::addOp));
}

template <typename T>
IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const
{
	return (this->_castOperand(rhs, operationType::subOp));
}

template <typename T>
IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const
{
	return (this->_castOperand(rhs, operationType::mulOp));
}

template <typename T>
IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const
{
	return (this->_castOperand(rhs, operationType::divOp));
}

template <typename T>
IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const
{
	return (this->_castOperand(rhs, operationType::modOp));
}

template <typename T>
void	TOperand<T>::_findType( void )
{
	if (typeid(T) == typeid(int8_t))
	{
		this->_type = eOperandType::int8;
		this->_typeStr = "int8";
	}
	else if (typeid(T) == typeid(int16_t))
	{
		this->_type = eOperandType::int16;
		this->_typeStr = "int16";
	}
	else if (typeid(T) == typeid(int32_t))
	{
		this->_type = eOperandType::int32;
		this->_typeStr = "int32";
	}
	else if (typeid(T) == typeid(float))
	{
		this->_type = eOperandType::floatt;
		this->_typeStr = "float";
	}
	else if (typeid(T) == typeid(double))
	{
		this->_type = eOperandType::doublee;
		this->_typeStr = "double";
	}
}

#endif // ** TOPERAND_HPP ** //
