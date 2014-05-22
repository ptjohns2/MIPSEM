

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

	//EXT rt, rs, pos, size
	//INS rt, rs, pos, size
	//////////////////


	////////FIX DECODING WITH UNSIGNED/SIGNED VALUES ETC!@@ -config file toggle for each args?
	for(char c = '0'; c <= '9'; c++){
		cout <<  parse::hexCharToDigit(c) << '\n';
	}
	for(char c = 'a'; c <= 'f'; c++){
		cout <<  parse::hexCharToDigit(c) << '\n';
	}
	for(char c = 'A'; c <= 'F'; c++){
		cout <<  parse::hexCharToDigit(c) << '\n';
	}
	
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
	//^^^^^ decodedes to wrong order size/pos@@@@@


	
	int numTests = 1000000;
	vector<string> invalidinstructions;
	vector<string> validinstructions;
	time_t start;
	time(&start);
	for(int i=0; i<numTests; i++){
		int instr = rand() * (((rand() % 2) == 0)? 1 : -1);

		Instruction nextPtr, loopPtr = d.buildInstruction(instr);
		if(loopPtr.getId() != NULL){

			Instruction nextPtr = e.buildInstruction(loopPtr.getAsmString());
			if(nextPtr.getId() != NULL){
			}
			if(loopPtr.getBin() != nextPtr.getBin()){
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
	*/


	return 0;
}
