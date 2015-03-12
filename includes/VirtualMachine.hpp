
#ifndef VIRTUALMACHINE_HPP
# define VIRTUALMACHINE_HPP

#include <list>
#include <map>
#include <boost/lexical_cast.hpp>
#include "parser.hpp"
#include "VmStack.hpp"
#include "OperandFactory.hpp"


class VirtualMachine
{


private:
	const std::list<avm_instruct> &						_instruct;
	VmStack<IOperand const *>							_stack;

	typedef IOperand const * (VirtualMachine::*IOperandFunctionPtr)(std::string const & value) const;
	typedef void  (VirtualMachine::*instructionFunctionPtr)(avm_instruct const &);

	std::map<std::string, eOperandType>					_typeMap;
	std::map<std::string, instructionFunctionPtr>		_functionInstruction;

	//ICI NEW
	OperandFactory										_operandFactory;

	//EXIT
	bool												_exit;

	VirtualMachine();
	VirtualMachine& operator=(VirtualMachine const &);

	void		_deleteStack( void );
	void		_checkStack( size_t value, avm_instruct const & instruction );

public:
	VirtualMachine( const std::list<avm_instruct> & instruct );
	~VirtualMachine( void );
	void	execute( void );

	void pushVM( avm_instruct const & instruction );
	void assertVM( avm_instruct const & instruction );
	void popVM( avm_instruct const & instruction );
	void dumpVM( avm_instruct const & instruction );
	void addVM( avm_instruct const & instruction );
	void subVM( avm_instruct const & instruction );
	void mulVM( avm_instruct const & instruction );
	void divVM( avm_instruct const & instruction );
	void modVM( avm_instruct const & instruction );
	void exitVM( avm_instruct const & instruction );
	void printVM( avm_instruct const & instruction );

	class VirtualMachineExecException : public std::runtime_error
	{
	private:
		VirtualMachineExecException const & operator=(VirtualMachineExecException const &) throw();
		VirtualMachineExecException() throw();

	public:
		VirtualMachineExecException(std::string const & errorMsg) throw();
		~VirtualMachineExecException() throw();
		virtual const char* 		what() const throw();

	};

	class VirtualMachineException : public std::runtime_error
	{
	private:
		VirtualMachineException const & operator=(VirtualMachineException const &) throw();
		VirtualMachineException() throw();

	public:
		VirtualMachineException(std::string const & errorMsg) throw();
		~VirtualMachineException() throw();

	};

	class VmInstructionException : public std::runtime_error
	{
	private:
		VmInstructionException const & operator=(VmInstructionException const &) throw();
		VmInstructionException() throw();
		avm_instruct const &		_errorInstr;


	public:
		VmInstructionException(std::string const & errorMsg, avm_instruct const & instruction) throw();
		~VmInstructionException() throw();
		virtual const char* 		what() const throw();

	};

};

#endif // ** VIRTUALMACHINE ** //

