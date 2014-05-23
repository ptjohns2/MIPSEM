#include "Instruction.hpp"

Instruction::Instruction(){
	id = NULL;
	asmString = "";
	binString = "";
	bin = 0x0;
}
Instruction::Instruction(InstructionData* id, string asmString, string binString, instr bin, vector<int> arguments)
	:id(id), asmString(asmString), binString(binString), bin(bin), arguments(arguments)
{

}

Instruction::~Instruction(){
	
}

//	Methods
InstructionData* Instruction::getId()const{return id;}
string Instruction::getAsmString()const{return asmString;}
string Instruction::getBinString()const{return binString;}
instr Instruction::getBin()const{return bin;}
vector<int> Instruction::getArguments()const{return arguments;}







