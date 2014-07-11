#include "BitResolver.hpp"

#include "Parser.hpp"

#include <bitset>
#include <cassert>
#include <iostream>

//	Constructors
BitResolver::BitResolver(InstructionDataBank* bank){
	addInstructionDataBank(bank);
}
BitResolver::~BitResolver(){
	//no heap data
}


//	public Methods
void BitResolver::addInstructionDataBank(InstructionDataBank* bank){
	for(int i=0; i<bank->size(); i++){
		InstructionData* tmpInstructionData = bank->get(i);
		int opcode = tmpInstructionData->getOpcode();
		table[opcode].push_back(tmpInstructionData);
	}
}


InstructionData* BitResolver::getInstructionData(instr ins){
	int opcode = ins >> (INSTRUCTIONSIZE - OPCODESIZE);
	for(int i=0; i<table[opcode].size(); i++){
		if(instrIsMatch(table[opcode][i], ins)){
			return table[opcode][i];
		}
	}
	return NULL;
}


//	private Methods
bool BitResolver::instrIsMatch(InstructionData* id, instr ins){
	instr maskedInstr = ins & id->getMask();
	return id->getFace() == maskedInstr;
}


