
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
	Assembler assembler = Assembler();
	assembler.setEncoder(&encoder);
	

	
	//string programName = "macrotest.txt";
	//string programName = "labeltest.txt";
	//string programName = "recursiontest.txt";
	//string programName = "prime-2.s";
	//string programName = "primes.txt";
	//string programName = "myTest.txt";
	string programName = "prime-1.txt";
	//string programName = "testProgram2.txt";
	assembler.loadProgramFromFile(programName);
	assembler.splitLabels();
	assembler.extractMacroDefinitions();
	//vector<string> testest = assembler.macroDB[0].buildMacro("test($t0, labelName");
	assembler.replaceEqv();
	assembler.pseudoInstructionPad();
	assembler.alignRawProgram();
	assembler.pseudoInstructionReplace();
	assembler.replaceLabels();
	assembler.writeAlignedRawProgramToDisk(programName + ".obj.txt");
	assembler.mapAlignedProgramToVirtualMemory();

	string objectFileName = "tmpObject.obj";
	assembler.virtualMemory.serialize(objectFileName);
	cpu.MEM.deserialize(objectFileName);
	
	cpu.run();




	

	return 0;
}

