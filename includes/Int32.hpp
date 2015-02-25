
#ifndef INT32_HPP
# define INT32_HPP

#include <boost/lexical_cast.hpp>
#include "eOperandType.hpp"
#include "IOperand.hpp"

class Int32 : public IOperand
{

private:
	int				_value;
	// int				_precision;
	eOperandType 	_type;
	std::string		_strValue;

	Int32();

public:
	Int32(std::string value);
	Int32( const Int32 & src);
	Int32& operator=(const Int32 & src);
	~Int32();

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

#endif // ** INT32_HPP ** //