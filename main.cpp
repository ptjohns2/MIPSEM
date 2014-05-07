
#include "encode.hpp"
#include "decode.hpp"
#include "InstructionDataBank.hpp"
#include "BitResolver.hpp"
#include "StringResolver.hpp"
#include "stringManip.hpp"
#include "mnemonics.hpp"
#include "Assembler.hpp"
#include "Disassembler.hpp"



#include <cassert>
#include <fstream>
#include <iostream>
#include <bitset>
#include <limits.h>
#include <ctime>

using namespace std;

int main(){
	assert(sizeof(float) == 4);
	assert(sizeof(int) == 4);

	InstructionDataBank bank = InstructionDataBank();
	
	ifstream instructionFile;
	instructionFile.open("instructions.txt");
	if (!instructionFile.is_open()){
		cout << "int main()::ERROR: cannot open file";
		getchar();
		return 0;
	}
	string tmpStr;

	while(getline(instructionFile, tmpStr, '\n')){
		bank.add(tmpStr);
	}

	Assembler a = Assembler(&bank);
	Disassembler d = Disassembler(&bank);

	Instruction* ptr = a.assemble("jr $t0");
	Instruction* ptr1 = a.assemble("addi $t0, $t1, 1");
	Instruction* ptr2 = a.assemble("add $t0, $t0, $t1 #234324 test");
	Instruction* ptr3 = a.assemble("sub $t0, $t1, $t3");
	Instruction* ptr4 = a.assemble("cfc1 $t0, $f2");


	Instruction* ptr5 = d.disassemble(0x00000000);
	Instruction* ptr6 = d.disassemble(0x46000005);
	Instruction* ptr7 = d.disassemble(0x00000020);
	Instruction* ptr8 = d.disassemble(0x20000005);
	
	

	Instruction* ptrB = d.disassemble(0x00114143);

	Instruction* ptrC = a.assemble("sra	$t0, $s1, 5");
	Instruction* ptrF = a.assemble("sra	$t0, $s1, 6");

	Instruction* ptrD = a.assemble("mul $t0, $t7, $s3");
	Instruction* ptrE = a.assemble("addi $t0, $t0, -1");
	Instruction* ptrE2 = d.disassemble(554237951);
	Instruction* ptrG = a.assemble("trunc.w.s $f0, $f2");
	Instruction* ptrH = a.assemble("sb $t0, 5($t2)");


	Instruction* ptrZ1 = d.disassemble(0x1509FFEF);

	
	getchar();


	delete ptrB, ptrC, ptrD, ptrE, ptrE2, ptrF, ptrG, ptrH;
	delete ptrZ1;

	
	delete ptr, ptr1, ptr2, ptr3, ptr4;
	delete ptr5, ptr6, ptr7, ptr8;


	vector<string> invalidinstructions;
	vector<string> validinstructions;
	for(unsigned int i=0; i<1000; i++){
		int instr = rand() * ((rand() % 2 == 0)? 1 : -1);

		Instruction* nextPtr = NULL, *loopPtr = d.disassemble(instr);
		if(loopPtr != NULL){
			//cout << instr << '\t' << loopPtr->asmString << '\t';

			Instruction* nextPtr = a.assemble(loopPtr->asmString);
			if(nextPtr != NULL){
				//cout << nextPtr->bin;
			}
			if(loopPtr->bin != nextPtr->bin){
				bool chk = true;
				for(int n=0; n<invalidinstructions.size(); n++){
					if(nextPtr->id->getName() == invalidinstructions[n]){
						chk = false;
						break;
					}
				}
				if(chk){
					invalidinstructions.push_back(nextPtr->id->getName());
				}
				//cout << "\t<-------";
			}else{
				bool chk = true;
				for(int n=0; n<validinstructions.size(); n++){
					if(nextPtr->id->getName() == validinstructions[n]){
						chk = false;
						break;
					}
				}
				if(chk){
					validinstructions.push_back(nextPtr->id->getName());
				}
			}
			//cout << '\n';
		}
		//getchar();

		delete loopPtr;
		loopPtr = NULL;
		delete nextPtr;
		nextPtr = NULL;
	}


	getchar();

	return 0;
}
