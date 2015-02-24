
#include "VirtualMachine.hpp"

// VirtualMachine::VirtualMachine(std::list<avm_instruct> instruct)// : _instruct(instruct)
VirtualMachine::VirtualMachine( void )// : _instruct(instruct)
{
	this->_typeMap["int8"] = eOperandType::int8;
	this->_typeMap["int16"] = eOperandType::int16;
	this->_functionFactory[eOperandType::int8] = &VirtualMachine::createInt8;
	this->_functionFactory[eOperandType::int16] = &VirtualMachine::createInt16;
	// this->_functionFactory[eOperandType::int8] = &(this->createInt8);
	// this->_functionFactory[eOperandType::int16] = &(this->createInt16);
//	this->execute();
}

void	VirtualMachine::addInstructions(std::list<avm_instruct> & instruct)
{
	this->_instruct = instruct;
}


VirtualMachine::~VirtualMachine()
{

}

void	VirtualMachine::execute()
{
	std::list<avm_instruct>::iterator	it;
	std::list<avm_instruct>::iterator	ite = this->_instruct.end();
	eOperandType						type;

	//test
	for (it = this->_instruct.begin(); it != ite; it++)
	{
		if (it.instrType.type != "")
		{
			this->_stack.push(this->createOperand(this->_typeMap[it.instrType.type], boost::lexical_cast<std::string>(it.instrType.value)));
			std::cout << "Operand Created : " << it.instrType.type << std::endl;
		}
	}
}

IOperand const * VirtualMachine::createOperand( eOperandType type, std::string const & value ) const
{
	return this->_functionFactory[type](value);
}
IOperand const * VirtualMachine::createInt8( std::string const & value ) const
{
	Int8		newValue = new Int8(value);
	return newValue;
}

IOperand const * VirtualMachine::createInt16( std::string const & value ) const
{
	Int8		newValue = new Int8(value);
	return newValue;
}
