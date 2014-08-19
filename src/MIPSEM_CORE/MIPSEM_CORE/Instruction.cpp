#include "Instruction.hpp"

Instruction::Instruction(){
	instructionData = NULL;
	asmString = "";
	bin = 0x0;
	for(int i=0; i<NUMBER_OF_INSTRUCTION_PARAMETERS; i++){
		arguments[i] = 0x0;
	}
}
Instruction::Instruction(InstructionData* instructionData, string asmString, instr bin, int32_t arguments[NUMBER_OF_INSTRUCTION_PARAMETERS]){
	this->instructionData = instructionData;
	this->asmString = asmString;
	this->bin = bin;

	for(int i=0; i<NUMBER_OF_INSTRUCTION_PARAMETERS; i++){
		this->arguments[i] = arguments[i];
	}
}

Instruction::~Instruction(){
	
}

//	Methods
InstructionData* Instruction::getInstructionData()const{return instructionData;}
string Instruction::getAsmString()const{return asmString;}
instr Instruction::getBin()const{return bin;}
int32_t Instruction::getArgumentValue(int index)const{return arguments[index];}







