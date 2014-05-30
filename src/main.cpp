

#include "InstructionDataBank.hpp"
#include "CPU.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"
#include "parse.hpp"

#include <bitset>
#include <cassert>
#include <iostream>
#include <fstream>
#include <time.h>


using namespace std;

int main(){
	assert(sizeof(float) == 4);
	assert(sizeof(int) == 4);
	assert(sizeof(unsigned int) == 4);
	assert(sizeof(uint32_t) == 4);
	assert(sizeof(int32_t) == 4);
	assert(sizeof(uint64_t) == 8);
	assert(sizeof(int64_t) == 8);

	srand((unsigned int)time(NULL));
	InstructionDataBank bank = InstructionDataBank();
	bank.loadFile("instructions.txt");
	Encoder e = Encoder(&bank);
	Decoder d = Decoder(&bank);
	BitResolver br = BitResolver(&bank);
	StringResolver sr = StringResolver(&bank);
	CPU cpu = CPU();

	float asdf = 2352.23;
	int64_t asdfg = (int64_t)asdf;
	float asdfgh = (float)(asdfg);


	string instrArr[10] = {
		"addi $t0, $zero, 9",
		"addi $t1, $zero, -1",
		"clo $1, $t1",
		"clz $2, $t1",};
				
	for(int i=0; i<4; i++){
		Instruction instr = e.buildInstruction(instrArr[i]);
		cpu.executeInstruction(&instr);
	}


	int wait = 0x101u;
	//////////
	
	////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////        Instruction get arguments - make faster (array not vector etc)        ///////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////
	


	int numTests = 10000;
	vector<string> invalidinstructions;
	vector<string> validinstructions;
	vector<pair<Instruction, Instruction>> invalidArgumentInstructions;
	time_t start;
	time(&start);
	for(int i=0; i<numTests; i++){
		int instr = rand() * (((rand() % 2) == 0)? 1 : -1);

		Instruction nextPtr, loopPtr = d.buildInstruction(instr);
		if(loopPtr.getInstructionData() != NULL){

			Instruction nextPtr = e.buildInstruction(loopPtr.getAsmString());
			if(nextPtr.getInstructionData() != NULL){
				bool invalidEncode = false;
				invalidEncode |= loopPtr.getBin() != nextPtr.getBin();
				bool invalidArgumentValues = false;
				for(int argValTestIterator = 0; argValTestIterator<NUMBER_OF_ARGUMENTS; argValTestIterator++){
					invalidArgumentValues |= loopPtr.getArgumentValue(argValTestIterator) != nextPtr.getArgumentValue(argValTestIterator);
				}
				if(invalidArgumentValues){
					pair<Instruction, Instruction> tmp;
					tmp.first = loopPtr;
					tmp.second = nextPtr;
					invalidArgumentInstructions.push_back(tmp);
				}

				if(invalidEncode){
					bool chk = true;
					for(unsigned int n=0; n<invalidinstructions.size(); n++){
						if(nextPtr.getInstructionData()->getName() == invalidinstructions[n]){
							chk = false;
							break;
						}
					}
					if(chk){
						invalidinstructions.push_back(nextPtr.getInstructionData()->getName());
					}
				}else{
					bool chk = true;
					for(unsigned int n=0; n<validinstructions.size(); n++){
						if(nextPtr.getInstructionData()->getName() == validinstructions[n]){
							chk = false;
							break;
						}
					}
					if(chk){
						validinstructions.push_back(nextPtr.getInstructionData()->getName());
					}	
				}
			}
		}
	}
	time_t end;
	time(&end);
	time_t time = end - start;
	cout << "Time: " << time << '\n';
	cout << "numTests: " << numTests << '\n';
	cout << "Time per: " << (float)(time) / (float)(numTests);


	return 0;
}