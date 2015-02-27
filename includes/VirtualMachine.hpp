
#ifndef VIRTUALMACHINE_HPP
# define VIRTUALMACHINE_HPP

#include <list>
#include <map>
//#include <unordered_map>
#include <boost/lexical_cast.hpp>
#include "parser.hpp"
#include "VmStack.hpp"
// #include "IOperand.hpp"
// #include "TOperand.hpp"
#include "OperandFactory.hpp"

#include "Int8.hpp"
#include "Int16.hpp"


// struct eOperandHash
// {
// 	template <typename T>
// 	std::size_t operator()(T t) const
// 		{
// 			return static_cast<std::size_t>(t);
// 		}
// };

// class OperandFactory;

class VirtualMachine
{


private:
	const std::list<avm_instruct> &						_instruct;
	VmStack<IOperand const *>									_stack;
	//std::unordered_map<eOperandType, IOperandFunctionPtr, eOperandHash>			_functionFactory;
//	 std::map<eOperandType, IOperandFunctionPtr>			_functionFactory;

	typedef IOperand const * (VirtualMachine::*IOperandFunctionPtr)(std::string const & value) const;
	typedef void  (VirtualMachine::*instructionFunctionPtr)(instr_type const &);

	std::map<std::string, eOperandType>					_typeMap;
	// static const IOperandFunctionPtr 					_functionFactory[];
	std::map<std::string, instructionFunctionPtr>		_functionInstruction;

	//ICI NEW
	OperandFactory										_operandFactory;

	VirtualMachine();
	VirtualMachine& operator=(VirtualMachine const &);

public:
	VirtualMachine( const std::list<avm_instruct> & instruct );
	~VirtualMachine( void );
	// void	print_som(avm_instruct test);
	void	execute( void );
	// void	addInstructions(std::list<avm_instruct> & instruct);
	// IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	// IOperand const * createInt8( std::string const & value ) const;
	// IOperand const * createInt16( std::string const & value ) const;
	// IOperand const * createInt32( std::string const & value ) const;
	// IOperand const * createFloat( std::string const & value ) const;
	// IOperand const * createDouble( std::string const & value ) const;

	void pushVM( instr_type const & instruction );
	void assertVM( instr_type const & instruction );
	void popVM( instr_type const & instruction );
	void dumpVM( instr_type const & instruction );
	void addVM( instr_type const & instruction );
	void subVM( instr_type const & instruction );
	void exitVM( instr_type const & instruction );
	void printVM( instr_type const & instruction );

};

#endif // ** VIRTUALMACHINE ** //

