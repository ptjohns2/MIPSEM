
#include "InstructionDataBank.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

int main(){
	assert(sizeof(float) == 4);
	assert(sizeof(int) == 4);

	srand(time(NULL));

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

	Encoder a = Encoder(&bank);
	Decoder d = Decoder(&bank);
	BitResolver br = BitResolver(&bank);
	StringResolver sr = StringResolver(&bank);

	

	Instruction* ptr = a.encode("lw $t0, 4($t1)");
	Instruction* ptr1 = a.encode("jr $t0");
	Instruction* ptr2 = a.encode("addi $t0, $t0, 16 #234324 test");
	Instruction* ptr3 = a.encode("sub $t0, $t1, $t3");
	Instruction* ptr4 = a.encode("cfc1 $t0, $f2");

	
	Instruction* ptr5 = d.decode(0x00000000);
	Instruction* ptr6 = d.decode(0x46000005);
	Instruction* ptr7 = d.decode(0x00000020);
	Instruction* ptr8 = d.decode(0x20000005);
	
	

	Instruction* ptrB = d.decode(0x00114143);

	Instruction* ptrC = a.encode("sra	$t0, $s1, 5");
	Instruction* ptrF = a.encode("sra	$t0, $s1, 6");

	Instruction* ptrD = a.encode("mul $t0, $t7, $s3");
	Instruction* ptrE = a.encode("addi $t0, $t0, -1");
	Instruction* ptrE2 = d.decode(554237951);
	Instruction* ptrG = a.encode("trunc.w.s $f0, $f2");
	Instruction* ptrH = a.encode("sb $t0, 5($t2)");


	Instruction* ptrZ1 = d.decode(0x1509FFEF);

	int isdaf = 2;

	delete ptrB, ptrC, ptrD, ptrE, ptrE2, ptrF, ptrG, ptrH;
	delete ptrZ1;

	
	delete ptr, ptr1, ptr2, ptr3, ptr4;
	delete ptr5, ptr6, ptr7, ptr8;


	vector<string> invalidinstructions;
	vector<string> validinstructions;
	for(unsigned int i=0; i<1000000; i++){
		int instr = rand() * (((rand() % 2) == 0)? 1 : -1);

		Instruction* nextPtr = NULL, *loopPtr = d.decode(instr);
		if(loopPtr != NULL){
			//cout << instr << '\t' << loopPtr->asmString << '\t';

			Instruction* nextPtr = a.encode(loopPtr->asmString);
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




	return 0;
}
