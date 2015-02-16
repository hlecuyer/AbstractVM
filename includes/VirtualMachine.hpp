
#include "mutantstack.hpp"
#include "IOperand.hpp"

class VirtualMachine
{
private:
	const std::list<avm_instruct> _instruct;
	MutantStack<IOperand> _stack;

	VirtualMachine();
	VirtualMachine& operator=(VirtualMachine const &);

public:
	VirtualMachine(std::list<avm_instruct>);
	~VirtualMachine();
	void	print_som(avm_instruct test);
	void	execute();
	
};
