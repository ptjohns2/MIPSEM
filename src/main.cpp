
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
	Encoder a = Encoder(&bank);
	Decoder d = Decoder(&bank);
	BitResolver br = BitResolver(&bank);
	StringResolver sr = StringResolver(&bank);

	



	vector<string> invalidinstructions;
	vector<string> validinstructions;
	for(unsigned int i=0; i<1000; i++){
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
