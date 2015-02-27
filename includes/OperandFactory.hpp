
#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

#include "IOperand.hpp"
#include "TOperand.hpp"

template <typename T>
class TOperand;

class OperandFactory
{
private:
	typedef IOperand const * (OperandFactory::*IOperandFunctionPtr)(std::string const & value) const;

	static const IOperandFunctionPtr 					_functionFactory[];
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	OperandFactory(OperandFactory const &);
	OperandFactory & operator=(OperandFactory const &);

public:
	OperandFactory();
	~OperandFactory();
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

};

#endif // ** OPERANDFACTORY_HPP ** //
