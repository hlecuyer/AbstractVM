
#ifndef INT16_HPP
# define INT16_HPP

#include <boost/lexical_cast.hpp>
#include "eOperandType.hpp"
#include "IOperand.hpp"

class Int16 : IOperand
{

private:
	int				_value;
	// int				_precision;
	eOperandType 	_type;
	std::string		_strValue;

	Int16();

public:
	Int16(std::string value);
	Int16( const Int16 & src);
	Int16& operator=(const Int16 & src);
	~Int16();

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

#endif // ** INT16_HPP ** //
