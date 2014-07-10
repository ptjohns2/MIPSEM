

#include "InstructionDataBank.hpp"
#include "CPU.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"
#include "MemoryMap.hpp"
#include "parse.hpp"
#include "VirtualMemory.hpp"

#include <bitset>
#include <cassert>
#include <iomanip>
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
	




	MemoryMap mem = MemoryMap();
	string fileName = "testSerialization.obj";

	char str1[] = "=testing, testing, one, two three, 1, 2, 3!=";
	char str2[] = "=sorry=";
	char str3[] = "=1234567890!@#$%^&*()=";
	vector<char*> strings;
	strings.push_back(&str1[0]);
	strings.push_back(&str2[0]);
	strings.push_back(&str3[0]);
	
	for(int i=0; i<strings.size(); i++){
		size_t memsize = strlen(strings[i]) + 1;
		char* tmpCharPtr = new char[memsize];
		memcpy(tmpCharPtr, &strings[i][0], memsize);
		MemorySegment* seg = new MemorySegment(memsize, 0, (h_byte*)tmpCharPtr);
		mem.addMemorySegment(*seg);
	}

	mem.serialize(fileName);
	

	MemoryMap readMem = MemoryMap(fileName);






	InstructionDataBank bank = InstructionDataBank();
	Decoder d = Decoder(&bank);
	Encoder e = Encoder(&bank, &d);
	BitResolver br = BitResolver(&bank);
	StringResolver sr = StringResolver(&bank);
	CPU cpu = CPU();

	VirtualMemory vm = VirtualMemory();
	vm.setDecoder(&d);


	
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
		Instruction instruction = e.buildInstruction(instrStrArr[i]);
		instr instructionBin = instruction.getBin();
		vm.writeToVirtualMemorySpace(cpu.PC + i * sizeof(instr), sizeof(instr), &instructionBin);
	}

	int asdfas = 3;
	
	while(true){
		Instruction* instructionFromMemory = vm.readInstruction(cpu.PC);
		cout << "\nPC = " << cpu.PC << " [" << instructionFromMemory->getAsmString() << "]\t\t\t\t";
		cpu.executeInstruction(instructionFromMemory);
	}

	

	return 0;
}

