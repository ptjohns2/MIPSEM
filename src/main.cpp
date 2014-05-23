

#include "InstructionDataBank.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"
#include "parse.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int main(){
	assert(sizeof(float) == 4);
	assert(sizeof(int) == 4);
	srand((unsigned int)time(NULL));
	InstructionDataBank bank = InstructionDataBank();
	bank.loadFile("instructions.txt");
	Encoder e = Encoder(&bank);
	Decoder d = Decoder(&bank);
	BitResolver br = BitResolver(&bank);
	StringResolver sr = StringResolver(&bank);
	
	//////////
	Instruction p;
	p = e.buildInstruction("lw $t1, -1($zero)");
	p = d.buildInstruction("10001100000010011111111111111111");

	p = e.buildInstruction("addi $t0, $t1, 0xFFF");
	p = d.buildInstruction("00100001001010000000111111111111");
	p = e.buildInstruction("addiu $t0, $t1, 0b11111111111111111111111111111111");
	p = d.buildInstruction("00100101001010001111111111111111");

	p = e.buildInstruction("sub $t0, $t0, $t1");
	p = d.buildInstruction("00000001000010010100000000100010");


	p = e.buildInstruction("EXT $t0, $t0, 0, 0");
	p = d.buildInstruction("01111101000010001111100000000000");
	p = e.buildInstruction("INS $t0, $t0, 5, 9");
	p = d.buildInstruction("01111101000010000110100101000100");

	
	int numTests = 10000;
	vector<string> invalidinstructions;
	vector<string> validinstructions;
	vector<pair<Instruction, Instruction>> invalidArgumentInstructions;
	time_t start;
	time(&start);
	for(int i=0; i<numTests; i++){
		int instr = rand() * (((rand() % 2) == 0)? 1 : -1);

		Instruction nextPtr, loopPtr = d.buildInstruction(instr);
		if(loopPtr.getId() != NULL){

			Instruction nextPtr = e.buildInstruction(loopPtr.getAsmString());
			if(nextPtr.getId() != NULL){
				bool invalidEncode = false;
				invalidEncode |= loopPtr.getBin() != nextPtr.getBin();
				vector<int> lArgs = loopPtr.getArguments();
				vector<int> nArgs = nextPtr.getArguments();
				bool invalidArgumentValues = false;
				invalidArgumentValues |= lArgs.size() != nArgs.size();

				int numArgs = (lArgs.size() < nArgs.size())? lArgs.size() : nArgs.size();
				for(int argValTestIterator = 0; argValTestIterator<numArgs; argValTestIterator++){
					invalidArgumentValues |= lArgs[argValTestIterator] != nArgs[argValTestIterator];
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
						if(nextPtr.getId()->getName() == invalidinstructions[n]){
							chk = false;
							break;
						}
					}
					if(chk){
						invalidinstructions.push_back(nextPtr.getId()->getName());
					}
				}else{
					bool chk = true;
					for(unsigned int n=0; n<validinstructions.size(); n++){
						if(nextPtr.getId()->getName() == validinstructions[n]){
							chk = false;
							break;
						}
					}
					if(chk){
						validinstructions.push_back(nextPtr.getId()->getName());
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
	


	/*
	int numTests = 1000000;
	vector<string> invalidinstructions;
	vector<string> validinstructions;
	time_t start;
	time(&start);

	
	for(unsigned int i=0; i<numTests; i++){
		int instr = rand() * (((rand() % 2) == 0)? 1 : -1);
		Instruction instruction = d.buildInstruction(instr);
	}

	time_t end;
	time(&end);
	time_t time = end - start;
	cout << "Time: " << time << '\n';
	cout << "numTests: " << numTests << '\n';
	cout << "Time per: " << (float)(time) / (float)(numTests);
	s*/


	return 0;
}
