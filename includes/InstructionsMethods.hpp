
#ifndef INSTRUCTIONMETHODS_HPP
# define INSTRUCTIONMETHODS_HPP

class InstructionsMethods
{
private:
	InstructionsMethods();
	~InstructionsMethods();
	InstructionsMethods(InstructionsMethods const &);
	InstructionsMethods & operator=(InstructionsMethods const &);

public:
	static push(avm_instruct instruction, VmStack & stack);
	static assert(avm_instruct instruction, VmStack & stack);
	static pop(avm_instruct instruction, VmStack & stack);
}

#endif // ** INSTRUCTIONMETHODS_HPP ** //
