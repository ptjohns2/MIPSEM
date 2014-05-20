
#include "InstructionDataBank.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int main(){
	assert(sizeof(float) == 4);
	assert(sizeof(int) == 4);
	srand(time(NULL));
	InstructionDataBank bank = InstructionDataBank();
	bank.loadFile("instructions.txt");
	Encoder e = Encoder(&bank);
	Decoder d = Decoder(&bank);
	BitResolver br = BitResolver(&bank);
	StringResolver sr = StringResolver(&bank);

	//EXT rt, rs, pos, size
	//INS rt, rs, pos, size
	//////////////////


	////////FIX DECODING WITH UNSIGNED/SIGNED VALUES ETC!@@ -config file toggle for each args?



	//////////
	Instruction p;
	p = e.buildInstruction("lw $zero, -1($zero)");
	p = e.buildInstruction("sub $t0, $t0, $t1");
	p = d.buildInstruction("00000000000000000000000000000000");


	p = e.buildInstruction("EXT $zero, $zero, 31, 31");
	p = d.buildInstruction("01111100000000001111011111000000");
	p = e.buildInstruction("INS $t0, $zero, 5, 2");
	p = d.buildInstruction("01111100000010000001000110000100");
	//^^^^^ decodedes to wrong order size/pos@@@@@

	vector<string> invalidinstructions;
	vector<string> validinstructions;
	for(unsigned int i=0; i<1000; i++){
		int instr = rand() * (((rand() % 2) == 0)? 1 : -1);

		Instruction nextPtr, loopPtr = d.buildInstruction(instr);
		if(loopPtr.id != NULL){

			Instruction nextPtr = e.buildInstruction(loopPtr.asmString);
			if(nextPtr.id != NULL){
			}
			if(loopPtr.bin != nextPtr.bin){
				bool chk = true;
				for(int n=0; n<invalidinstructions.size(); n++){
					if(nextPtr.id->getName() == invalidinstructions[n]){
						chk = false;
						break;
					}
				}
				if(chk){
					invalidinstructions.push_back(nextPtr.id->getName());
				}
			}else{
				bool chk = true;
				for(int n=0; n<validinstructions.size(); n++){
					if(nextPtr.id->getName() == validinstructions[n]){
						chk = false;
						break;
					}
				}
				if(chk){
					validinstructions.push_back(nextPtr.id->getName());
				}
			}
		}
	}




	return 0;
}
