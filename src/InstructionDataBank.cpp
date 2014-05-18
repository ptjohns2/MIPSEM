#include "InstructionDataBank.hpp"

#include <iostream>
#include <fstream>



//class InstructionDataBank
//	Constructors
InstructionDataBank::InstructionDataBank()
{

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
}

int InstructionDataBank::size(){
	return bank.size();
}

void InstructionDataBank::loadFile(string filename){
	ifstream instructionFile;
	instructionFile.open(filename);
	if (!instructionFile.is_open()){
		cout << "int main()::ERROR: cannot open file";
		getchar();
	}
	string tmpStr;

	while(getline(instructionFile, tmpStr, '\n')){
		add(tmpStr);
	}
}


InstructionData* InstructionDataBank::operator[](const int index){
	return bank[index];
}

