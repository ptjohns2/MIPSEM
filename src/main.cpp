
#include "Assembler.hpp"
#include "CPU.hpp"
#include "Decoder.hpp"
#include "InstructionDataBank.hpp"
#include "Encoder.hpp"
#include "MemoryMap.hpp"
#include "Parser.hpp"
#include "VirtualMemory.hpp"

#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <time.h>
#include <unordered_map>


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
	Decoder decoder = Decoder(&bank);
	Encoder encoder = Encoder(&bank, &decoder);
	BitResolver bitResolver = BitResolver(&bank);
	StringResolver stringResolver = StringResolver(&bank);
	CPU cpu = CPU();
	VirtualMemory vm = VirtualMemory();
	vm.setDecoder(&decoder);
	Parser parser = Parser();
	/*
	fstream file("test.txt");
	string tmpTest;
	while(getline(file, tmpTest)){
		int val = parser.literals.getLiteralValue(tmpTest);
 		cout << tmpTest << "\t" << val << '\n';
	}
	*/
	fstream file("strtest.txt");
	string tmpStr;
	getline(file, tmpStr);

	string adsjcf = parser.literals.getStringLiteralValue(tmpStr);


	int asdfjksdfasdkf = 1;
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	
	vector<string> instrStrArr;
	instrStrArr.push_back("addi $t1, $zero, 48");	//0
	instrStrArr.push_back("addi	$t0, $zero, 0");	//4

	instrStrArr.push_back("addi $t0, $t0, 8");	//8
	instrStrArr.push_back("addi	$v0, $zero, 1");	//12
	instrStrArr.push_back("add	$a0, $zero, $t0");	//16
	
	instrStrArr.push_back("syscall");	//20

	instrStrArr.push_back("beq $t0, $t1, 1");	//24
	instrStrArr.push_back("b -6");

	instrStrArr.push_back("addi $a0, $zero, 9999");	//28
	instrStrArr.push_back("syscall");	//32

	for(int i=0; i<instrStrArr.size(); i++){
		Instruction instruction = encoder.buildInstruction(instrStrArr[i]);
		instr instructionBin = instruction.getBin();
		vm.writeToVirtualMemorySpace(cpu.PC + i * sizeof(instr), sizeof(instr), &instructionBin);
	}

	int asdfas = 3;
	
	int num = 0;
	while(true){
		num++;
		if(num > 100000){
			getchar();
		}

		Instruction* instructionFromMemory = vm.readInstruction(cpu.PC);
		cout << "\nPC = " << cpu.PC << " [" << instructionFromMemory->getAsmString() << "]\t\t\t\t";
		cpu.executeInstruction(instructionFromMemory);
	}

	

	return 0;
}

