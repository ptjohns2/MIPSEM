#include "Instruction.hpp"

Instruction::Instruction(){
	id = NULL;
	asmString = "";
	binString = "";
	bin = 0x0;
}
Instruction::Instruction(InstructionData* id, string asmString, string binString, instr bin, vector<int64_t> arguments)
	:id(id), asmString(asmString), binString(binString), bin(bin), arguments(arguments)
{

}

Instruction::~Instruction(){
	
}

//	Methods
InstructionData* Instruction::getId(){return id;}
string Instruction::getAsmString(){return asmString;}
string Instruction::getBinString(){return binString;}
instr Instruction::getBin(){return bin;}
vector<int64_t> Instruction::getArguments(){return arguments;}







