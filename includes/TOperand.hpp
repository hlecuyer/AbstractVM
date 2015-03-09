
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

	class OperandOverflowException : public std::runtime_error
	{
	private:
		OperandOverflowException const & operator=(OperandOverflowException const &) throw();

	public:
		OperandOverflowException( void ) throw();
		~OperandOverflowException( void ) throw();
		virtual const char* 		what() const throw();

	};

	class OperandUnderflowException : public std::runtime_error
	{
	private:
		OperandUnderflowException const & operator=(OperandUnderflowException const &) throw();

	public:
		OperandUnderflowException( void ) throw();
		~OperandUnderflowException( void ) throw();
		virtual const char* 		what( void ) const throw();

	};

	class OperandZeroOperationException : public std::runtime_error
	{
	private:
		OperandZeroOperationException const & operator=(OperandZeroOperationException const &) throw();

	public:
		OperandZeroOperationException( void ) throw();
		~OperandZeroOperationException( void ) throw();
		virtual const char* 		what( void ) const throw();

	};

	class OperandOperationException : public std::runtime_error
	{
	private:
		OperandOperationException const & operator=(OperandOperationException const &) throw();
		OperandOperationException() throw();
		std::string				_operandStr(eOperandType type) const throw();
		std::string				_operationStr( void ) const throw();
		const char *											_errType;
		operationType											_operation;
		std::pair<eOperandType, std::string>					_leftValue;
		std::pair<eOperandType, std::string>					_rightValue;

	public:
		OperandOperationException(const char * errType, operationType operation, std::pair<eOperandType, std::string> leftValue, std::pair<eOperandType, std::string> rightValue) throw();
		~OperandOperationException() throw();
		virtual const char* 		what() const throw();

	};

	class OperandCreationCastException : public std::runtime_error
	{
	private:
		OperandCreationCastException const & operator=(OperandCreationCastException const &) throw();
		OperandCreationCastException() throw();

	public:
		OperandCreationCastException(const char * error) throw();
		~OperandCreationCastException() throw();
		virtual const char* 		what() const throw();

	};
};

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
		throw TOperand<T>::OperandOverflowException();
	if (b < 0 && a < std::numeric_limits<Q>::lowest() - b)
		throw TOperand<T>::OperandUnderflowException();
	return (a + b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_subOp (Q a, Q b) const
{
	if (b > 0 && a > std::numeric_limits<Q>::max() + b)
		throw TOperand<T>::OperandOverflowException();
	if (b < 0 && a < std::numeric_limits<Q>::lowest() + b)
		throw TOperand<T>::OperandUnderflowException();
	return (a - b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_mulOp (Q a, Q b) const
{
	if (((a > 0 && b > 0) || (a < 0 && b < 0)) && a > std::numeric_limits<Q>::max() / b)
		throw TOperand<T>::OperandOverflowException();
	if (((a > 0 && b < 0) || (a < 0 && b > 0)) && a < std::numeric_limits<Q>::lowest() / b)
		throw TOperand<T>::OperandUnderflowException();
	return (a * b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_divOp (Q a, Q b) const
{
	if (b == 0)
		throw TOperand<T>::OperandZeroOperationException();
	if (((a > 0 && b > 0) || (a < 0 && b < 0)) && a > std::numeric_limits<Q>::max() * b)
		throw TOperand<T>::OperandOverflowException();
	if (((a > 0 && b < 0) || (a < 0 && b > 0)) && a < std::numeric_limits<Q>::lowest() * b)
		throw TOperand<T>::OperandUnderflowException();
	return (a / b);
}

template <typename T>
template <typename Q>
Q TOperand<T>::_modOp (Q a, Q b) const
{
	if (b == 0)
		throw TOperand<T>::OperandZeroOperationException();
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

	try
	{
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
	}
	catch(std::exception & e)
	{
		throw TOperand<T>::OperandOperationException(e.what(), operation, std::pair<eOperandType, std::string>(this->_type, this->_strValue), std::pair<eOperandType, std::string>(rhs->getType(), rhs->toString()));
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
		throw OperandCreationCastException(e.what());
		// std::cout << "AbstractVM: " << this->_typeStr << ": " << e.what() << std::endl;
		// std::exit(-1);
	}
	catch ( boost::numeric::negative_overflow & e)
	{
		throw OperandCreationCastException(e.what());
		// std::cout << "AbstractVM: " << this->_typeStr << ": " << e.what() << std::endl;
		// std::exit(-1);
	}
	catch ( boost::bad_lexical_cast const & e)
	{
		throw OperandCreationCastException(e.what());
		// std::cout << "AbstractVM: " << this->_typeStr << ": " << e.what() <<  std::endl;
		// std::exit(-1);
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

template <typename T>
TOperand<T>::OperandOverflowException::OperandOverflowException( void ) throw() : std::runtime_error("")
{

}

template <typename T>
const char*					TOperand<T>::OperandOverflowException::what() const throw()
{
	std::string ret = "Overflow Exception";
	return ret.c_str();
}

template <typename T>
TOperand<T>::OperandOverflowException::~OperandOverflowException() throw()
{
	return ;
}


template <typename T>
TOperand<T>::OperandUnderflowException::OperandUnderflowException( void ) throw() : std::runtime_error("")
{

}

template <typename T>
const char*					TOperand<T>::OperandUnderflowException::what() const throw()
{
	std::string ret = "Underflow Exception";
	return ret.c_str();
}

template <typename T>
TOperand<T>::OperandUnderflowException::~OperandUnderflowException() throw()
{
	return ;
}


template <typename T>
TOperand<T>::OperandZeroOperationException::OperandZeroOperationException( void ) throw() : std::runtime_error("")
{

}

template <typename T>
const char*					TOperand<T>::OperandZeroOperationException::what() const throw()
{
	std::string ret = "Operation with zero exception";
	return ret.c_str();
}

template <typename T>
TOperand<T>::OperandZeroOperationException::~OperandZeroOperationException() throw()
{
	return ;
}


template <typename T>
TOperand<T>::OperandOperationException::OperandOperationException(const char * errType, operationType operation, std::pair<eOperandType, std::string> leftValue, std::pair<eOperandType, std::string> rightValue) throw()
	: std::runtime_error(""), _errType(errType), _operation(operation), _leftValue(leftValue), _rightValue(rightValue)
{
}

template <typename T>
const char*					TOperand<T>::OperandOperationException::what() const throw()
{
	std::string leftVal = this->_operandStr(this->_leftValue.first) + "(" + this->_leftValue.second + ")";
	std::string rightVal = this->_operandStr(this->_rightValue.first) + "(" + this->_rightValue.second + ")";

	std::string ret = std::string("AbstractVM: ") + this->_errType + std::string(" on operation '") + this->_operationStr() + std::string("' with operands ")
		+ leftVal + " and " + rightVal;
	return ret.c_str();
}

template <typename T>
TOperand<T>::OperandOperationException::~OperandOperationException() throw()
{
	return ;
}

template <typename T>
std::string					TOperand<T>::OperandOperationException::_operandStr(eOperandType type) const throw()
{
	switch (type)
	{
	case eOperandType::int8 :
		return "int8";
	case eOperandType::int16 :
		return "int16";
	case eOperandType::int32 :
		return "int32";
	case eOperandType::floatt :
		return "float";
	case eOperandType::doublee :
		return "double";
	}
	return "";
}

template <typename T>
std::string					TOperand<T>::OperandOperationException::_operationStr( void ) const throw()
{
	switch (this->_operation)
	{
	case operationType::addOp :
		return "add";
	case operationType::subOp :
		return "sub";
	case operationType::mulOp :
		return "mul";
	case operationType::divOp :
		return "div";
	case operationType::modOp :
		return "mod";
	}
	return "";
}

template <typename T>
TOperand<T>::OperandCreationCastException::OperandCreationCastException( const char * error ) throw() : std::runtime_error(error)
{

}

template <typename T>
const char*					TOperand<T>::OperandCreationCastException::what() const throw()
{
	std::string ret = "Abstract VM : " + std::string(std::runtime_error::what());
	return ret.c_str();
}

template <typename T>
TOperand<T>::OperandCreationCastException::~OperandCreationCastException() throw()
{
	return ;
}

#endif // ** TOPERAND_HPP ** //
