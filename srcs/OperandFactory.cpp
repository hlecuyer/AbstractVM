
#include "OperandFactory.hpp"
#include "TOperand.hpp"
// template <typename T>
// class TOperand;

const OperandFactory::IOperandFunctionPtr OperandFactory::_functionFactory[] =
{
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble
};

OperandFactory::OperandFactory()
{

}

OperandFactory::~OperandFactory()
{

}

IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
	TOperand<int8_t> *		newValue = new TOperand<int8_t>(value);
	return newValue;
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const
{
	TOperand<int16_t> *		newValue = new TOperand<int16_t>(value);
	return newValue;
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const
{
	TOperand<int32_t> *		newValue = new TOperand<int32_t>(value);
	return newValue;
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
	TOperand<float> *		newValue = new TOperand<float>(value);
	return newValue;
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
	TOperand<double> *		newValue = new TOperand<double>(value);
	return newValue;
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	return (this->*(_functionFactory[type]))(value);
}
