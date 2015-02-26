
#ifndef INT8_HPP
# define INT8_HPP

#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include "eOperandType.hpp"
#include "IOperand.hpp"

class Int8 : public IOperand
{

private:
	char			_value;
//	const int		_precision;
	eOperandType 	_type;
	std::string		_strValue;

	Int8();

public:
	Int8(std::string value);
	Int8(const Int8 & );
	Int8& operator=(const Int8 &);
	~Int8();

	int getPrecision( void ) const;
	eOperandType getType( void ) const;
	IOperand const * operator+( IOperand const & rhs ) const;
	IOperand const * operator-( IOperand const & rhs ) const;
	IOperand const * operator*( IOperand const & rhs ) const;
	IOperand const * operator/( IOperand const & rhs ) const;
	IOperand const * operator%( IOperand const & rhs ) const;
	std::string const & toString( void ) const;
	void validateVal(int const & val) const;
	// ~IOperand( void ) {}

};


#endif // ** INT8_HPP ** //
