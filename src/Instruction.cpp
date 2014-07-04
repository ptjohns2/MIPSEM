#include "Instruction.hpp"

Instruction::Instruction(){
	instructionData = NULL;
	asmString = "";
	binString = "";
	bin = 0x0;
	for(int i=0; i<NUMBER_OF_PARAMETERS; i++){
		arguments[i] = 0x0;
	}
}
Instruction::Instruction(InstructionData* instructionData, string asmString, string binString, instr bin, vector<int> arguments)
	:instructionData(instructionData), asmString(asmString), binString(binString), bin(bin)
{
	for(int i=0; i<arguments.size(); i++){
		this->arguments[i] = arguments[i];
	}
	for(int i=arguments.size(); i<NUMBER_OF_PARAMETERS; i++){
		this->arguments[i] = 0x0;
	}
}

Instruction::~Instruction(){
	
}

//	Methods
InstructionData* Instruction::getInstructionData()const{return instructionData;}
string Instruction::getAsmString()const{return asmString;}
string Instruction::getBinString()const{return binString;}
instr Instruction::getBin()const{return bin;}
uint32_t Instruction::getArgumentValue(int index)const{return arguments[index];}







