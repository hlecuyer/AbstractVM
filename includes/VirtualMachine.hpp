
#ifndef VIRTUALMACHINE_HPP
# define VIRTUALMACHINE_HPP

#include <list>
#include <map>
//#include <unordered_map>
#include <boost/lexical_cast.hpp>
#include "parser.hpp"
#include "VmStack.hpp"
#include "IOperand.hpp"
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

class VirtualMachine
{


private:
	const std::list<avm_instruct> &						_instruct;
	VmStack<IOperand const *>									_stack;
	//std::unordered_map<eOperandType, IOperandFunctionPtr, eOperandHash>			_functionFactory;
//	 std::map<eOperandType, IOperandFunctionPtr>			_functionFactory;

	typedef IOperand const * (VirtualMachine::*IOperandFunctionPtr)(std::string const & value) const;
	std::map<std::string, eOperandType>					_typeMap;
	static const IOperandFunctionPtr 					_functionFactory[];

	VirtualMachine();
	VirtualMachine& operator=(VirtualMachine const &);

public:
	VirtualMachine( const std::list<avm_instruct> & instruct );
	~VirtualMachine( void );
	// void	print_som(avm_instruct test);
	void	execute( void );
	// void	addInstructions(std::list<avm_instruct> & instruct);
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

};

#endif // ** VIRTUALMACHINE ** //

