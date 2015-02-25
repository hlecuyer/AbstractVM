
#ifndef FLOAT_HPP
# define FLOAT_HPP

#include <boost/lexical_cast.hpp>
#include "eOperandType.hpp"
#include "IOperand.hpp"

class Float : public IOperand
{

private:
	float				_value;
	// int				_precision;
	eOperandType 	_type;
	std::string		_strValue;

	Float();

public:
	Float(std::string value);
	Float( const Float & src);
	Float& operator=(const Float & src);
	~Float();

	int getPrecision( void ) const;
	eOperandType getType( void ) const;
	IOperand const * operator+( IOperand const & rhs ) const;
	IOperand const * operator-( IOperand const & rhs ) const;
	IOperand const * operator*( IOperand const & rhs ) const;
	IOperand const * operator/( IOperand const & rhs ) const;
	IOperand const * operator%( IOperand const & rhs ) const;
	std::string const & toString( void ) const;
	// ~IOperand( void ) {}

};

#endif // ** FLOAT_HPP ** //