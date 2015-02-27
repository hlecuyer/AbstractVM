
#include "VirtualMachine.hpp"
#include "Int8.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Float.hpp"
#include "Double.hpp"
#include "TOperand.hpp"

class TOperand;

VirtualMachine::VirtualMachine(const std::list<avm_instruct> & instruct) : _instruct(instruct)
// VirtualMachine::VirtualMachine( void )// : _instruct(instruct)
{
	this->_typeMap["int8"] = eOperandType::int8;
	this->_typeMap["int16"] = eOperandType::int16;
	this->_typeMap["int32"] = eOperandType::int32;
	this->_typeMap["float"] = eOperandType::floatt;
	this->_typeMap["double"] = eOperandType::doublee;


	// this->_functionInstruction["add"] = &VirtualMachine::int8;
	this->_functionInstruction["push"] = &VirtualMachine::pushVM;
	this->_functionInstruction["pop"] = &VirtualMachine::popVM;
	this->_functionInstruction["assert"] = &VirtualMachine::assertVM;
	this->_functionInstruction["dump"] = &VirtualMachine::dumpVM;
	this->_functionInstruction["add"] = &VirtualMachine::addVM;
	// this->_functionInstruction["double"] = &VirtualMachine::doublee;

//	this->_functionFactory[static_cast<int>(eOperandType::int8)] = &createInt8;
//	this->_functionFactory[static_caste<int>(OperandType::int16)] = &createInt16;
	// this->_functionFactory.insert(this->_functionFactory.begin(), std::pair<eOperandType, IOperandFunctionPtr>(eOperandType::int8, &VirtualMachine::createInt8));
	// this->_functionFactory.insert(this->_functionFactory.begin(), std::pair<eOperandType, IOperandFunctionPtr>(eOperandType::int16, &VirtualMachine::createInt16));
	// std::make_pair(eOperandType::int8, &VirtualMachine::createInt8);
//	this->_functionFactory.insert(this->_functionFactory.begin(), std::make_pair(eOperandType::int8, &VirtualMachine::createInt8));
//	this->_functionFactory.insert(this->_functionFactory.begin(), std::make_pair(eOperandType::int16, &VirtualMachine::createInt16));
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

const VirtualMachine::IOperandFunctionPtr VirtualMachine::_functionFactory[] =
{
	&VirtualMachine::createInt8,
	&VirtualMachine::createInt16,
	&VirtualMachine::createInt32,
	&VirtualMachine::createFloat,
	&VirtualMachine::createDouble
};

void	VirtualMachine::execute()
{
	std::list<avm_instruct>::const_iterator	it;
	std::list<avm_instruct>::const_iterator	ite = this->_instruct.end();
//	eOperandType						type;
	// std::map<std::string, eOperandType>::const_iterator					found;
	std::map<std::string, instructionFunctionPtr>::const_iterator			found;

	//test
	for (it = this->_instruct.begin(); it != ite; it++)
	{
		found = this->_functionInstruction.find(it->name);
		if (found != this->_functionInstruction.end())
		{
			// (*(found->second))(it->instrType);
			(this->*(_functionInstruction[it->name]))(it->instrType);
		}
		else
		{
			std::cout << "Instruction not found : " <<  it->name << std::endl;
		}
		// if (it->instrType.type != "")
		// {
		// 	found = this->_typeMap.find(it->instrType.type);
		// 	if (found != this->_typeMap.end())
		// 	{
		// 		this->_stack.push(this->createOperand(found->second, it->instrType.value));
		// 		// this->_stack.push(this->createOperand(this->_typeMap[it->instrType.type], boost::lexical_cast<std::string>(it->instrType.value)));
		// 		std::cout << "Operand Created : " << it->instrType.type << std::endl;
		// 	}
		// 	else
		// 		std::cout << "not working !" << std::endl;
		// }
	}

	// VmStack<IOperand const *>::iterator	sIt;
	// VmStack<IOperand const *>::iterator	sIte = this->_stack.end();
	// for (sIt = this->_stack.begin(); sIt != sIte; sIt++)
	// {
	// 	std::cout << (*sIt)->toString() << std::endl;
	// }
}

IOperand const * VirtualMachine::createOperand( eOperandType type, std::string const & value ) const
{
//	std::unordered_map<eOperandType, IOperandFunctionPtr>::const_iterator					found;
//	std::map<eOperandType, IOperandFunctionPtr>::const_iterator					found;

	// found = this->_functionFactory.find(type);
	// if (found != this->_functionFactory.end())
	// {
	// 	return (*found->second)(value);
	// 	// return this->_functionFactory[type](value);
	// }
	// return NULL;

	return (this->*(_functionFactory[type]))(value);
}

IOperand const * VirtualMachine::createInt8( std::string const & value ) const
{
	// Int8 *		newValue = new Int8(value);
	TOperand<int8_t> *		newValue = new TOperand<int8_t>(value);
	return newValue;
}

IOperand const * VirtualMachine::createInt16( std::string const & value ) const
{
	// Int16 *		newValue = new Int16(value);
	TOperand<int16_t> *		newValue = new TOperand<int16_t>(value);
	return newValue;
}

IOperand const * VirtualMachine::createInt32( std::string const & value ) const
{
	// Int32 *		newValue = new Int32(value);
	TOperand<int32_t> *		newValue = new TOperand<int32_t>(value);
	return newValue;
}

IOperand const * VirtualMachine::createFloat( std::string const & value ) const
{
	// Float *		newValue = new Float(value);
	TOperand<float> *		newValue = new TOperand<float>(value);
	return newValue;
}

IOperand const * VirtualMachine::createDouble( std::string const & value ) const
{
	// Double *		newValue = new Double(value);
	TOperand<double> *		newValue = new TOperand<double>(value);
	return newValue;
}

void VirtualMachine::pushVM(instr_type const & instruction)
{
	std::map<std::string, eOperandType>::const_iterator					found;

	found = this->_typeMap.find(instruction.type);
	if (found != this->_typeMap.end())
	{
		this->_stack.push(this->createOperand(found->second, instruction.value));
		// this->_stack.push(this->createOperand(this->_typeMap[instruction.type], boost::lexical_cast<std::string>(instruction.value)));
		std::cout << "Operand Created : " << instruction.type << std::endl; //DEBUG
	}
	else
	{
		std::cout << "AbstractVM: wrong, not working !" << std::endl;
	}
}

void VirtualMachine::assertVM(instr_type const & instruction)
{
	(void)instruction;

}

void VirtualMachine::popVM(instr_type const & instruction)
{
	static_cast<void>(instruction);
	this->_stack.pop();
}

void VirtualMachine::dumpVM(instr_type const & instruction)
{
	VmStack<IOperand const *>::iterator		sIt;
	VmStack<IOperand const *>::iterator		sIte = this->_stack.end();

	static_cast<void>(instruction);
	for (sIt = this->_stack.begin(); sIt != sIte; sIt++)
	{
		std::cout << (*sIt)->toString() << std::endl;
	}
}

void VirtualMachine::addVM(instr_type const & instruction)
{
	// (void)instruction;
	std::cout << "ici fonction add de la VM " << std::endl;
	/* OK ici ! */
	IOperand const * tmp1;
	IOperand const * tmp2;
	IOperand const * result;

	static_cast<void>(instruction);
	if (this->_stack.size() < 2)
	{
		std::cout << "EXCEPTION PAS ASSEZ STACK !" << std::endl;
		exit(-1);
	}
	tmp1 = this->_stack.top();
	this->_stack.pop();
	tmp2 = this->_stack.top();
	this->_stack.pop();
	result = *tmp1 + *tmp2;
	this->_stack.push(result);
}
