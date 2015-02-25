
#ifndef DOUBLE_HPP
# define DOUBLE_HPP

#include <boost/lexical_cast.hpp>
#include "eOperandType.hpp"
#include "IOperand.hpp"

class Double : public IOperand
{

private:
	double				_value;
	// int				_precision;
	eOperandType 	_type;
	std::string		_strValue;

	Double();

public:
	Double(std::string value);
	Double( const Double & src);
	Double& operator=(const Double & src);
	~Double();

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

#endif // ** DOUBLE_HPP ** //