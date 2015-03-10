
#include "VirtualMachine.hpp"
#include "TOperand.hpp"


VirtualMachine::VirtualMachine(const std::list<avm_instruct> & instruct) : _instruct(instruct)
{
	this->_typeMap["int8"] = eOperandType::int8;
	this->_typeMap["int16"] = eOperandType::int16;
	this->_typeMap["int32"] = eOperandType::int32;
	this->_typeMap["float"] = eOperandType::floatt;
	this->_typeMap["double"] = eOperandType::doublee;


	this->_functionInstruction["push"] = &VirtualMachine::pushVM;
	this->_functionInstruction["pop"] = &VirtualMachine::popVM;
	this->_functionInstruction["assert"] = &VirtualMachine::assertVM;
	this->_functionInstruction["dump"] = &VirtualMachine::dumpVM;
	this->_functionInstruction["add"] = &VirtualMachine::addVM;
	this->_functionInstruction["sub"] = &VirtualMachine::subVM;
	this->_functionInstruction["mul"] = &VirtualMachine::subVM;
	this->_functionInstruction["div"] = &VirtualMachine::subVM;
	this->_functionInstruction["mod"] = &VirtualMachine::modVM;
	this->_functionInstruction["exit"] = &VirtualMachine::exitVM;
	this->_functionInstruction["print"] = &VirtualMachine::printVM;
}


VirtualMachine::~VirtualMachine()
{

}

void	VirtualMachine::execute()
{
	std::list<avm_instruct>::const_iterator									it;
	std::list<avm_instruct>::const_iterator									ite = this->_instruct.end();
	std::map<std::string, instructionFunctionPtr>::const_iterator			found;

	try
	{
	for (it = this->_instruct.begin(); it != ite; it++)
	{
		found = this->_functionInstruction.find(it->name);
		if (found != this->_functionInstruction.end())
		{
			(this->*(_functionInstruction[it->name]))(*it);
		}
		// else
		// {
		// 	throw VirtualMachineException("Instruction not found."); //DEBUG
		// }
	}
	throw VirtualMachineException("No exit in file.");
	}
	catch (std::exception & e)
	{
		throw VirtualMachineExecException(e.what());
	}
}


void VirtualMachine::pushVM(avm_instruct const & instruction)
{
	std::map<std::string, eOperandType>::const_iterator					found;

	found = this->_typeMap.find(instruction.instrType.type);
	if (found != this->_typeMap.end())
	{
		this->_stack.push(this->_operandFactory.createOperand(found->second, instruction.instrType.value));

		std::cout << "Operand Created : " << instruction.instrType.type << std::endl; //DEBUG
	}
	// else
	// {
	// 	std::cout << "AbstractVM: wrong, not working !" << std::endl; //DEBUG
	// }
}

void VirtualMachine::assertVM(avm_instruct const & instruction)
{
	std::cout << "ici fonction assert de la VM " << std::endl;
	std::map<std::string, eOperandType>::const_iterator					found;
	IOperand const *													assertValue;

	this->_checkStack(1, instruction);
	found = this->_typeMap.find(instruction.instrType.type);
	if (found != this->_typeMap.end())
	{
		assertValue = this->_operandFactory.createOperand(found->second, instruction.instrType.value);
		if (this->_stack.top()->getType() != assertValue->getType() || this->_stack.top()->toString() != assertValue->toString())
			throw VmInstructionException("Failed assert", instruction);
		delete assertValue;

		std::cout << "Operand Assert : " << instruction.instrType.type << std::endl; //DEBUG
	}
}

void VirtualMachine::popVM(avm_instruct const & instruction)
{
	IOperand const * tmp;

	static_cast<void>(instruction);
	if (this->_stack.size() == 0)
		throw VmInstructionException("Pop on empty stack", instruction);
	tmp = this->_stack.top();
	this->_stack.pop();
	delete tmp;
}

void VirtualMachine::dumpVM(avm_instruct const & instruction)
{
	VmStack<IOperand const *>::iterator		sIt = this->_stack.begin();
	VmStack<IOperand const *>::iterator		sIte;

	static_cast<void>(instruction);
	if (this->_stack.size() > 0)
	{
		for (sIte = --this->_stack.end(); sIte != sIt; sIte--)
		{
			std::cout << (*sIte)->toString() << std::endl;
		}
		std::cout << (*sIte)->toString() << std::endl;
	}
}

void VirtualMachine::addVM(avm_instruct const & instruction)
{
	// (void)instruction;
	std::cout << "ici fonction add de la VM " << std::endl;
	/* OK ici ! */
	IOperand const * v1;
	IOperand const * v2;
	IOperand const * result;

	// static_cast<void>(instruction);
	this->_checkStack(2, instruction);
	// if (this->_stack.size() < 2)
	// {
	// 	throw VmInstructionException("Less than two value on stack", instruction);
	// 	// std::cout << "EXCEPTION PAS ASSEZ STACK !" << std::endl;
	// 	// exit(-1);
	// }
	v1 = this->_stack.top();
	this->_stack.pop();
	v2 = this->_stack.top();
	this->_stack.pop();
	// std::cout << "ici" << std::endl;
	result = *v1 + *v2;
	// std::cout << "la" << std::endl;
	this->_stack.push(result);
	delete v1;
	delete v2;
}

void VirtualMachine::subVM(avm_instruct const & instruction)
{
	// (void)instruction;
	std::cout << "ici fonction sub de la VM " << std::endl;
	/* OK ici ! */
	IOperand const * v1;
	IOperand const * v2;
	IOperand const * result;

	static_cast<void>(instruction);
	this->_checkStack(2, instruction);
	// if (this->_stack.size() < 2)
	// {
	// 	throw VmInstructionException("Less than two value on stack", instruction);
	// 	// std::cout << "EXCEPTION PAS ASSEZ STACK !" << std::endl;
	// 	// exit(-1);
	// }
	v1 = this->_stack.top();
	this->_stack.pop();
	v2 = this->_stack.top();
	this->_stack.pop();
	result = *v2 - *v1;
	this->_stack.push(result);
	delete v1;
	delete v2;
}

void VirtualMachine::mulVM(avm_instruct const & instruction)
{
	// (void)instruction;
	std::cout << "ici fonction mul de la VM " << std::endl;
	/* OK ici ! */
	IOperand const * v1;
	IOperand const * v2;
	IOperand const * result;

	static_cast<void>(instruction);
	this->_checkStack(2, instruction);
	// if (this->_stack.size() < 2)
	// {
	// 	throw VmInstructionException("Less than two value on stack", instruction);
	// 	// std::cout << "EXCEPTION PAS ASSEZ STACK !" << std::endl;
	// 	// exit(-1);
	// }
	v1 = this->_stack.top();
	this->_stack.pop();
	v2 = this->_stack.top();
	this->_stack.pop();
	result = *v2 * *v1;
	this->_stack.push(result);
	delete v1;
	delete v2;
}

void VirtualMachine::divVM(avm_instruct const & instruction)
{
	// (void)instruction;
	std::cout << "ici fonction div de la VM " << std::endl;
	/* OK ici ! */
	IOperand const * v1;
	IOperand const * v2;
	IOperand const * result;

	static_cast<void>(instruction);
	this->_checkStack(2, instruction);
	// if (this->_stack.size() < 2)
	// {
	// 	throw VmInstructionException("Less than two value on stack", instruction);
	// 	// std::cout << "EXCEPTION PAS ASSEZ STACK !" << std::endl;
	// 	// exit(-1);
	// }
	v1 = this->_stack.top();
	this->_stack.pop();
	v2 = this->_stack.top();
	this->_stack.pop();
	result = *v2 / *v1;
	this->_stack.push(result);
	delete v1;
	delete v2;
}

void VirtualMachine::modVM(avm_instruct const & instruction)
{
	// (void)instruction;
	std::cout << "ici fonction mod de la VM " << std::endl;
	/* OK ici ! */
	IOperand const * v1;
	IOperand const * v2;
	IOperand const * result;

	static_cast<void>(instruction);
	this->_checkStack(2, instruction);
	// if (this->_stack.size() < 2)
	// {
	// 	throw VmInstructionException("Less than two value on stack", instruction);
	// 	// std::cout << "EXCEPTION PAS ASSEZ STACK !" << std::endl;
	// 	// exit(-1);
	// }
	v1 = this->_stack.top();
	this->_stack.pop();
	v2 = this->_stack.top();
	this->_stack.pop();
	result = *v2 % *v1;
	this->_stack.push(result);
	delete v1;
	delete v2;
}

void VirtualMachine::_checkStack( size_t value, avm_instruct const & instruction )
{
	if (this->_stack.size() < value)
	{
		std::string ret = "Less than " + std::to_string(value) + " value(s) on the stack";
		throw VmInstructionException(ret, instruction);
	}
}

void VirtualMachine::_deleteStack( void )
{
	IOperand const *						tmp;

	while (this->_stack.size() > 0)
	{
		tmp = this->_stack.top();
		this->_stack.pop();
		delete tmp;
	}
}

void VirtualMachine::exitVM(avm_instruct const & instruction)
{
	// IOperand const *						tmp;

	static_cast<void>(instruction);
	this->_deleteStack();
	// faire des delete !!
	std::exit(0);
}

void VirtualMachine::printVM(avm_instruct const & instruction)
{
	static_cast<void>(instruction);
	this->_checkStack(1, instruction);
	// if (this->_stack.size() < 1)
	// {
	// 	throw VmInstructionException("Empty stack", instruction);
	// 	//mettre error !!
	// 	// std::exit(-1);
	// }
	// else
	// {
		if (this->_stack.top()->getPrecision() == 0)
		{
			TOperand<int8_t> const *		addr;

			addr = reinterpret_cast<TOperand<int8_t> const *>(this->_stack.top());
			std::cout << static_cast< const char>(addr->getValue()) << std::endl;
		}
		else
		{
			throw VmInstructionException("Incorrect operand", instruction);
			//mettre error !!
			// std::exit(-1);
		}
	// }
}

// **************** //
// ** EXCEPTIONS ** //
// **************** //

VirtualMachine::VirtualMachineException::VirtualMachineException( std::string const & errorMsg ) throw()
	: std::runtime_error(errorMsg)
{
}

VirtualMachine::VirtualMachineException::~VirtualMachineException() throw()
{
	return ;
}

VirtualMachine::VmInstructionException::VmInstructionException( std::string const & errorMsg, avm_instruct const & instruction ) throw()
	: std::runtime_error(errorMsg), _errorInstr(instruction)
{
}

const char*					VirtualMachine::VmInstructionException::what() const throw()
{
	// std::string test = getErrType();
	std::string val = "";
	if (this->_errorInstr.instrType.type != "")
		val = " " + this->_errorInstr.instrType.type + "(" + this->_errorInstr.instrType.value + ")";
	// std::string ret = "AbstractVM: " + std::string(std::runtime_error::what()) + " : on instruction \"" + this->_errorInstr.name + val + "\"";
	std::string ret = std::string(std::runtime_error::what()) + " : on instruction \"" + this->_errorInstr.name + val + "\"";
	return ret.c_str();
}

VirtualMachine::VmInstructionException::~VmInstructionException() throw()
{
	return ;
}


VirtualMachine::VirtualMachineExecException::VirtualMachineExecException( std::string const & errorMsg ) throw()
	: std::runtime_error(errorMsg)
{

}

const char*					VirtualMachine::VirtualMachineExecException::what() const throw()
{
	// std::string test = getErrType();
	std::string ret = "VirtualMachine : " + std::string(std::runtime_error::what());

 	// std::string val = "";
	// if (this->_errorInstr.instrType.type != "")
	// 	val = " " + this->_errorInstr.instrType.type + "(" + this->_errorInstr.instrType.value + ")";
	// std::string ret = "AbstractVM: " + std::string(std::runtime_error::what()) + " : on instruction \"" + this->_errorInstr.name + val + "\"";
	return ret.c_str();
}

VirtualMachine::VirtualMachineExecException::~VirtualMachineExecException() throw()
{
	return ;
}
