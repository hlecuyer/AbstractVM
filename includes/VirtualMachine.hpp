
#ifndef VIRTUALMACHINE_HPP
# define VIRTUALMACHINE_HPP

#include <list>
#include <map>
#include <boost/lexical_cast.hpp>
#include "parser.hpp"
#include "VmStack.hpp"
#include "IOperand.hpp"

class VirtualMachine
{
private:
	std::list<avm_instruct>								_instruct;
	VmStack<IOperand>									_stack;
	std::map<eOperandType, IOperand *f(std::string)>	_functionFactory;
	std::map<std::string, eOperandType>					_typeMap;

	// VirtualMachine();
	VirtualMachine& operator=(VirtualMachine const &);

public:
	VirtualMachine( void );
	~VirtualMachine( void );
	// void	print_som(avm_instruct test);
	void	execute( void );
	void	addInstructions(std::list<avm_instruct> & instruct);
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;

};

#endif // ** VIRTUALMACHINE ** //

