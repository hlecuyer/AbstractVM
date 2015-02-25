
#include "VirtualMachine.hpp"

VirtualMachine::VirtualMachine(const std::list<avm_instruct> & instruct) : _instruct(instruct)
// VirtualMachine::VirtualMachine( void )// : _instruct(instruct)
{
	this->_typeMap["int8"] = eOperandType::int8;
	this->_typeMap["int16"] = eOperandType::int16;
	// this->_functionFactory.insert(this->_functionFactory.begin(), std::pair<eOperandType, IOperandFunctionPtr>(eOperandType::int8, &VirtualMachine::createInt8));
	// this->_functionFactory.insert(this->_functionFactory.begin(), std::pair<eOperandType, IOperandFunctionPtr>(eOperandType::int16, &VirtualMachine::createInt16));
	// std::make_pair(eOperandType::int8, &VirtualMachine::createInt8);
	this->_functionFactory.insert(this->_functionFactory.begin(), std::make_pair(eOperandType::int8, &VirtualMachine::createInt8));
	this->_functionFactory.insert(this->_functionFactory.begin(), std::make_pair(eOperandType::int16, &VirtualMachine::createInt16));
	// this->_functionFactory = {{eOperandType::int8, &VirtualMachine::createInt8}, {eOperandType::int16, &VirtualMachine::createInt16}};
	// this->_functionFactory[eOperandType::int8] = &VirtualMachine::createInt8;
	// this->_functionFactory[eOperandType::int16] = &VirtualMachine::createInt16;
	// this->_functionFactory[eOperandType::int8] = &(this->createInt8);
	// this->_functionFactory[eOperandType::int16] = &(this->createInt16);
//	this->execute();
}

// void	VirtualMachine::addInstructions(std::list<avm_instruct> & instruct)
// {
// 	this->_instruct = instruct;
// }


VirtualMachine::~VirtualMachine()
{

}

void	VirtualMachine::execute()
{
	std::list<avm_instruct>::const_iterator	it;
	std::list<avm_instruct>::const_iterator	ite = this->_instruct.end();
	eOperandType						type;
	std::map<std::string, eOperandType>::const_iterator					found;

	//test
	for (it = this->_instruct.begin(); it != ite; it++)
	{
		if (it->instrType.type != "")
		{
			found = this->_typeMap.find(it->instrType.type);
			if (found != this->_typeMap.end())
			{
				this->_stack.push(this->createOperand(found->second, boost::lexical_cast<std::string>(it->instrType.value)));
				// this->_stack.push(this->createOperand(this->_typeMap[it->instrType.type], boost::lexical_cast<std::string>(it->instrType.value)));
				std::cout << "Operand Created : " << it->instrType.type << std::endl;
			}
			else
				std::cout << "not working !" << std::endl;
		}
	}
}

IOperand const * VirtualMachine::createOperand( eOperandType type, std::string const & value ) const
{
	std::unordered_map<eOperandType, IOperandFunctionPtr>::const_iterator					found;
	// std::map<eOperandType, IOperandFunctionPtr>::const_iterator					found;

	found = this->_functionFactory.find(type);
	if (found != this->_functionFactory.end())
	{
		return (*found->second)(value);
		// return this->_functionFactory[type](value);
	}
	return NULL;
}

IOperand const * VirtualMachine::createInt8( std::string const & value ) const
{
	Int8 *		newValue = new Int8(value);
	return newValue;
}

IOperand const * VirtualMachine::createInt16( std::string const & value ) const
{
	Int16 *		newValue = new Int16(value);
	return newValue;
}
