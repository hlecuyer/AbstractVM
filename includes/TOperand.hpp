
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
	std::string			_typeStr;
	OperandFactory		_operandFactory;

	// template <typename Q>
	// struct operatorWrapper {
	// 	typedef Q (*operatorFunctionPtr)(Q a, Q b) const;
	// };

	// static const operatorWrapper::operatorFunctionPtr 					_operators[];

	TOperand();
	void		_findType( void );
	// IOperand const *	_addOperand( IOperand const & rhs ) const;
	template <typename C>
	IOperand const *	_addOperand( TOperand<C> const * rhs ) const ;

	template <typename C>
	IOperand const *	_subOperand( TOperand<C> const * rhs ) const ;

	template <typename C>
	IOperand const *	_mulOperand( TOperand<C> const * rhs ) const ;

	template <typename C>
	IOperand const *	_genericOperand( TOperand<C> const * rhs, operationType operation ) const ;

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
		// return this->_modOp<C>(a, b);
		break ;
	}
	return 0;
}


template <typename T>
template <typename Q>
Q TOperand<T>::_addOp (Q a, Q b) const
{
	return (a + b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_subOp (Q a, Q b) const
{
	return (a - b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_mulOp (Q a, Q b) const
{
	return (a * b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_divOp (Q a, Q b) const
{
	return (a / b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_modOp (Q a, Q b) const
{
	return (a % b);
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
		result = this->_operatorsSwitch<C> (newVal, rhs->getValue(), operation);
		ret = boost::lexical_cast<std::string>(result);
		type = rhs->getType();
	}
	else
	{
		T		newVal;
		T		result;

		newVal = boost::numeric_cast<T>(rhs->getValue());//VERIFIER EXCEPTION
		result = this->_operatorsSwitch<T> (this->_value, newVal, operation);
		ret = boost::lexical_cast<std::string>(result);
		type = this->getType();
	}
	return (this->_operandFactory.createOperand(type, ret));
}

// template <typename T>
// template <typename C>
// IOperand const *	TOperand<T>::_addOperand( TOperand<C> const * rhs ) const
// {
// 	std::string		ret;
// 	eOperandType	type;

// 	if (this->getPrecision() < rhs->getPrecision())
// 	{
// 		C		newVal;
// 		C		result;

// 		newVal = boost::numeric_cast<C>(this->_value);//VERIFIER EXCEPTION
// 		result = newVal + rhs->getValue();
// 		ret = boost::lexical_cast<std::string>(result);
// 		type = rhs->getType();
// 	}
// 	else
// 	{
// 		T		newVal;
// 		T		result;

// 		newVal = boost::numeric_cast<T>(rhs->getValue());//VERIFIER EXCEPTION
// 		result = this->_value + newVal;
// 		ret = boost::lexical_cast<std::string>(result);
// 		type = this->getType();
// 	}
// 	return (this->_operandFactory.createOperand(type, ret));
// }

// template <typename T>
// template <typename C>
// IOperand const *	TOperand<T>::_subOperand( TOperand<C> const * rhs ) const
// {
// 	std::string		ret;
// 	eOperandType	type;

// 	if (this->getPrecision() < rhs->getPrecision())
// 	{
// 		C		newVal;
// 		C		result;

// 		newVal = boost::numeric_cast<C>(this->_value);//VERIFIER EXCEPTION
// 		result = newVal - rhs->getValue();
// 		ret = boost::lexical_cast<std::string>(result);
// 		type = rhs->getType();
// 	}
// 	else
// 	{
// 		T		newVal;
// 		T		result;

// 		newVal = boost::numeric_cast<T>(rhs->getValue());//VERIFIER EXCEPTION
// 		result = this->_value - newVal;
// 		ret = boost::lexical_cast<std::string>(result);
// 		type = this->getType();
// 	}
// 	return (this->_operandFactory.createOperand(type, ret));
// }

// template <typename T>
// template <typename C>
// IOperand const *	TOperand<T>::_mulOperand( TOperand<C> const * rhs ) const
// {
// 	std::string		ret;
// 	eOperandType	type;

// 	if (this->getPrecision() < rhs->getPrecision())
// 	{
// 		C		newVal;
// 		C		result;

// 		newVal = boost::numeric_cast<C>(this->_value);//VERIFIER EXCEPTION
// 		result = newVal - rhs->getValue();
// 		ret = boost::lexical_cast<std::string>(result);
// 		type = rhs->getType();
// 	}
// 	else
// 	{
// 		T		newVal;
// 		T		result;

// 		newVal = boost::numeric_cast<T>(rhs->getValue());//VERIFIER EXCEPTION
// 		result = this->_value - newVal;
// 		ret = boost::lexical_cast<std::string>(result);
// 		type = this->getType();
// 	}
// 	return (this->_operandFactory.createOperand(type, ret));
// }

template <typename T>
TOperand<T>::TOperand(std::string value) : _strValue(value)
{
	// this->_type = this->_findType();
	this->_findType();
	// this->_type = TOperand::_findType();
	// this->_type = TOperand::_findType<T>();
	try
	{
		this->_value = boost::numeric_cast<T>(boost::lexical_cast<double>(value));
	}
	catch ( boost::numeric::positive_overflow & e)
	{
		std::cout << "AbstractVM: " << this->_typeStr << ": " << e.what() << std::endl;//MODFIER
		std::exit(-1);
	}
	catch ( boost::numeric::negative_overflow & e)
	{
		std::cout << "AbstractVM: " << this->_typeStr << ": " << e.what() << std::endl;//MODFIER
		std::exit(-1);
	}
	catch ( boost::bad_lexical_cast const & e)
	{
		std::cout << "AbstractVM: " << this->_typeStr << ": " << e.what() <<  std::endl;//MODFIER
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

template <typename T>
IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const
{
	switch (rhs.getType())
	{
	case eOperandType::int8 :
		return (this->_genericOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs), operationType::subOp ));
		break ;
	case eOperandType::int16 :
		return (this->_genericOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs), operationType::subOp ));
		break ;
	case eOperandType::int32 :
		return (this->_genericOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs), operationType::subOp ));
		break ;
	case eOperandType::floatt :
		return (this->_genericOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs), operationType::subOp ));
		break ;
	case eOperandType::doublee :
		return (this->_genericOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs), operationType::subOp ));
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
		return (this->_genericOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs), operationType::mulOp ));
		break ;
	case eOperandType::int16 :
		return (this->_genericOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs), operationType::mulOp ));
		break ;
	case eOperandType::int32 :
		return (this->_genericOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs), operationType::mulOp ));
		break ;
	case eOperandType::floatt :
		return (this->_genericOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs), operationType::mulOp ));
		break ;
	case eOperandType::doublee :
		return (this->_genericOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs), operationType::mulOp ));
		break ;
	}

	return this;
}

template <typename T>
IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const
{
	switch (rhs.getType())
	{
	case eOperandType::int8 :
		return (this->_genericOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs), operationType::divOp ));
		break ;
	case eOperandType::int16 :
		return (this->_genericOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs), operationType::divOp ));
		break ;
	case eOperandType::int32 :
		return (this->_genericOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs), operationType::divOp ));
		break ;
	case eOperandType::floatt :
		return (this->_genericOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs), operationType::divOp ));
		break ;
	case eOperandType::doublee :
		return (this->_genericOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs), operationType::divOp ));
		break ;
	}

	return this;
}

template <typename T>
IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const
{
	// switch (rhs.getType())
	// {
	// case eOperandType::int8 :
	// 	return (this->_genericOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs), operationType::modOp ));
	// 	break ;
	// case eOperandType::int16 :
	// 	return (this->_genericOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs), operationType::modOp ));
	// 	break ;
	// case eOperandType::int32 :
	// 	return (this->_genericOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs), operationType::modOp ));
	// 	break ;
	// case eOperandType::floatt :
	// 	std::cout << "ERROR NO MOD ON FLOAT !!" << std::endl;
	// 	// return (this->_genericOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs), operationType::modOp ));
	// 	break ;
	// case eOperandType::doublee :
	// 	std::cout << "ERROR NO MOD ON DOUBLE !!" << std::endl;
	// 	// return (this->_genericOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs), operationType::modOp ));
	// 	break ;
	// }
	(void)rhs;
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

// template <typename T>
// IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const
// {
// 	switch (rhs.getType())
// 	{
// 	case eOperandType::int8 :
// 		return (this->_subOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs)));
// 		break ;
// 	case eOperandType::int16 :
// 		return (this->_subOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs)));
// 		break ;
// 	case eOperandType::int32 :
// 		return (this->_subOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs)));
// 		break ;
// 	case eOperandType::floatt :
// 		return (this->_subOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs)));
// 		break ;
// 	case eOperandType::doublee :
// 		return (this->_subOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs)));
// 		break ;
// 	}

// 	return this;
// }

// template <typename T>
// IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const
// {
// 	switch (rhs.getType())
// 	{
// 	case eOperandType::int8 :
// 		return (this->_mulOperand<int8_t>(reinterpret_cast< TOperand<int8_t> const * >(&rhs)));
// 		break ;
// 	case eOperandType::int16 :
// 		return (this->_mulOperand<int16_t>( reinterpret_cast< TOperand<int16_t> const * >(&rhs)));
// 		break ;
// 	case eOperandType::int32 :
// 		return (this->_mulOperand<int32_t>(  reinterpret_cast< TOperand<int32_t> const * >(&rhs)));
// 		break ;
// 	case eOperandType::floatt :
// 		return (this->_mulOperand<float>(  reinterpret_cast< TOperand<float> const * >(&rhs)));
// 		break ;
// 	case eOperandType::doublee :
// 		return (this->_mulOperand<double>(  reinterpret_cast< TOperand<double> const * >(&rhs)));
// 		break ;
// 	}

// 	return this;
// }

// template <typename T>
// IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const
// {
// 	(void)rhs;
// 	return this;
// }

// template <typename T>
// IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const
// {
// 	(void)rhs;
// 	return this;
// }

template <typename T>
void	TOperand<T>::_findType( void )
{
	// switch (typeid(T))
	// {
	if (typeid(T) == typeid(int8_t))
	{
	// case typeid(int8_t) :
		this->_type = eOperandType::int8;
		this->_typeStr = "int8";
	}
	// 	break ;
	// case typeid(int16_t) :
	else if (typeid(T) == typeid(int16_t))
	{
		this->_type = eOperandType::int16;
		this->_typeStr = "int16";
	}
	// 	break ;
	// case typeid(int32_t) :
	else if (typeid(T) == typeid(int32_t))
	{
		this->_type = eOperandType::int32;
		this->_typeStr = "int32";
	}
	// 	break ;
	// case typeid(float) :
	else if (typeid(T) == typeid(float))
	{
		this->_type = eOperandType::floatt;
		this->_typeStr = "float";
	}
	// 	break ;
	// case typeid(double) :
	else if (typeid(T) == typeid(double))
	{
		this->_type = eOperandType::doublee;
		this->_typeStr = "double";
	}
		// break ;
	// }
	// if (typeid(T) == typeid(int8_t))
	// 	return eOperandType::int8;
	// else if (typeid(T) == typeid(int16_t))
	// 	return eOperandType::int16;
	// else if (typeid(T) == typeid(int32_t))
	// 	return eOperandType::int32;
	// else if (typeid(T) == typeid(float))
	// 	return eOperandType::floatt;

	// return eOperandType::doublee;
}

#endif // ** TOPERAND_HPP ** //
