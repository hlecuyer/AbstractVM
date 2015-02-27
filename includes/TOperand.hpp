
#ifndef TOPERAND_HPP
# define TOPERAND_HPP

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <stdexcept>
#include <typeinfo>
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
// #include "VirtualMachine.hpp"

// class VirtualMachine;
// class OperandFactory;

template <typename T>
class TOperand : public IOperand
{
private:
	T					_value;
	eOperandType 		_type;
	std::string			_strValue;
	OperandFactory		_operandFactory;

	// template <typename Q>
	// struct operatorWrapper {
	// 	typedef Q (*operatorFunctionPtr)(Q a, Q b) const;
	// };

	// static const operatorWrapper::operatorFunctionPtr 					_operators[];

	TOperand();
	eOperandType		_findType( void );
	template <typename C>
	// IOperand const *	_addOperand( IOperand const & rhs ) const;
	IOperand const *	_addOperand( TOperand<C> const * rhs ) const;

	template <typename C>
	IOperand const *	_subOperand( TOperand<C> const * rhs ) const;

	template <typename C>
	IOperand const *	_mulOperand( TOperand<C> const * rhs ) const;

	template <typename C>
	IOperand const *	_genericOperand( TOperand<C> const * rhs, operationType operation ) const;

	template <typename Q>
	Q _operatorsSwitch(Q a, Q b, operationType operation) const;

	template <typename Q>
	Q addOp(Q a, Q b);

	template <typename Q>
	Q subOp(Q a, Q b);

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

template <typename T>
template <typename Q>
Q _operatorsSwitch(Q a, Q b, operationType operation) const
{
	switch (operation)
	{
	case operationType::addOp :
		return this->addOp<Q>(a, b);
		break ;
	case operationType::subOp :
		return this->subOp<Q>(a, b);
		break ;
	case operationType::mulOp :
		// return this->addOp<Q>(a, b);
		break ;
	case operationType::divOp :
		// return this->addOp<Q>(a, b);
		break ;
	case operationType::modOp :
		// return this->addOp<Q>(a, b);
		break ;
	}
	return 0;
}

// template <typname>
// const operatorWrapper<Q>::operatorFunctionPtr TOperand<T>::_operators[] =
// {
// 	&TOperand::addOp,
// 	&TOperand::subOp
// };

template <typename T>
template <typename Q>
Q TOperand<T>::addOp (Q a, Q b)
{
	return (a + b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::subOp (Q a, Q b)
{
	return (a - b);
}

template <typename T>
template <typename C>
IOperand const *	TOperand<T>::_genericOperand( TOperand<C> const * rhs, operationType operation ) const
{
	std::string		ret;
	eOperandType	type;

	if (this->getPrecision() < rhs->getPrecision())
	{
		C		newVal;
		C		result;

		newVal = boost::numeric_cast<C>(this->_value);//VERIFIER EXCEPTION
		// result = newVal + rhs->getValue();
		result = this->_operatorsSwitch<C> (newVal, rhs->getValue());
		// result = (this->_operators[operation]<C>) (newVal, rhs->getValue());
		ret = boost::lexical_cast<std::string>(result);
		type = rhs->getType();
	}
	else
	{
		T		newVal;
		T		result;

		newVal = boost::numeric_cast<T>(rhs->getValue());//VERIFIER EXCEPTION
		// result = this->_value + newVal;
		result = this->_operatorsSwitch<T> (newVal, rhs->getValue());
		// result = (this->_operators[operation]<T>) (this->_value, newVal);
		ret = boost::lexical_cast<std::string>(result);
		type = this->getType();
	}
	return (this->_operandFactory.createOperand(type, ret));
}

template <typename T>
template <typename C>
IOperand const *	TOperand<T>::_addOperand( TOperand<C> const * rhs ) const
{
	std::string		ret;
	eOperandType	type;

	if (this->getPrecision() < rhs->getPrecision())
	{
		C		newVal;
		C		result;

		newVal = boost::numeric_cast<C>(this->_value);//VERIFIER EXCEPTION
		result = newVal + rhs->getValue();
		ret = boost::lexical_cast<std::string>(result);
		type = rhs->getType();
	}
	else
	{
		T		newVal;
		T		result;

		newVal = boost::numeric_cast<T>(rhs->getValue());//VERIFIER EXCEPTION
		result = this->_value + newVal;
		ret = boost::lexical_cast<std::string>(result);
		type = this->getType();
	}
	return (this->_operandFactory.createOperand(type, ret));
}

template <typename T>
template <typename C>
IOperand const *	TOperand<T>::_subOperand( TOperand<C> const * rhs ) const
{
	std::string		ret;
	eOperandType	type;

	if (this->getPrecision() < rhs->getPrecision())
	{
		C		newVal;
		C		result;

		newVal = boost::numeric_cast<C>(this->_value);//VERIFIER EXCEPTION
		result = newVal - rhs->getValue();
		ret = boost::lexical_cast<std::string>(result);
		type = rhs->getType();
	}
	else
	{
		T		newVal;
		T		result;

		newVal = boost::numeric_cast<T>(rhs->getValue());//VERIFIER EXCEPTION
		result = this->_value - newVal;
		ret = boost::lexical_cast<std::string>(result);
		type = this->getType();
	}
	return (this->_operandFactory.createOperand(type, ret));
}

template <typename T>
template <typename C>
IOperand const *	TOperand<T>::_mulOperand( TOperand<C> const * rhs ) const
{
	std::string		ret;
	eOperandType	type;

	if (this->getPrecision() < rhs->getPrecision())
	{
		C		newVal;
		C		result;

		newVal = boost::numeric_cast<C>(this->_value);//VERIFIER EXCEPTION
		result = newVal - rhs->getValue();
		ret = boost::lexical_cast<std::string>(result);
		type = rhs->getType();
	}
	else
	{
		T		newVal;
		T		result;

		newVal = boost::numeric_cast<T>(rhs->getValue());//VERIFIER EXCEPTION
		result = this->_value - newVal;
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
IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const
{
	switch (rhs.getType())
	{
	case eOperandType::int8 :
		return (this->_genericOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs), operationType::addOp ));
		break ;
	case eOperandType::int16 :
		return (this->_genericOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs), operationType::addOp ));
		break ;
	case eOperandType::int32 :
		return (this->_genericOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs), operationType::addOp ));
		break ;
	case eOperandType::floatt :
		return (this->_genericOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs), operationType::addOp ));
		break ;
	case eOperandType::doublee :
		return (this->_genericOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs), operationType::addOp ));
		break ;
	}

	return this;
}
// template <typename T>
// IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const
// {
// 	switch (rhs.getType())
// 	{
// 	case eOperandType::int8 :
// 		return (this->_addOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs)));
// 		break ;
// 	case eOperandType::int16 :
// 		return (this->_addOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs)));
// 		break ;
// 	case eOperandType::int32 :
// 		return (this->_addOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs)));
// 		break ;
// 	case eOperandType::floatt :
// 		return (this->_addOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs)));
// 		break ;
// 	case eOperandType::doublee :
// 		return (this->_addOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs)));
// 		break ;
// 	}

// 	return this;
// }

template <typename T>
IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const
{
	switch (rhs.getType())
	{
	case eOperandType::int8 :
		return (this->_subOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs)));
		break ;
	case eOperandType::int16 :
		return (this->_subOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs)));
		break ;
	case eOperandType::int32 :
		return (this->_subOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs)));
		break ;
	case eOperandType::floatt :
		return (this->_subOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs)));
		break ;
	case eOperandType::doublee :
		return (this->_subOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs)));
		break ;
	}

	return this;
}

template <typename T>
IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const
{
	switch (rhs.getType())
	{
	case eOperandType::int8 :
		return (this->_mulOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs)));
		break ;
	case eOperandType::int16 :
		return (this->_mulOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs)));
		break ;
	case eOperandType::int32 :
		return (this->_mulOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs)));
		break ;
	case eOperandType::floatt :
		return (this->_mulOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs)));
		break ;
	case eOperandType::doublee :
		return (this->_mulOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs)));
		break ;
	}

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
