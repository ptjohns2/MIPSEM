#include "InstructionDataBank.hpp"


//class InstructionDataBank
//	Constructors
InstructionDataBank::InstructionDataBank()
{
	size = 0;
}

InstructionDataBank::~InstructionDataBank()
{
	for(int i=0; i<bank.size(); i++){
		delete bank[i];
	}
}

//	Methods
void InstructionDataBank::add(string info){
	InstructionData* newInstr = new InstructionData(info);
	bank.push_back(newInstr);
	size++;
}

InstructionData* InstructionDataBank::operator[](const int index){
	return bank[index];
}