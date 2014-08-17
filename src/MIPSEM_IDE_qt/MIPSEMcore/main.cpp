#define _CRTDBG_MAPALLOC
#include <stdlib.h>
#include <crtdbg.h>



#include "Assembler.hpp"
#include "BitManip.hpp"
#include "CPU.hpp"
#include "Decoder.hpp"
#include "Exceptions.hpp"
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
	/*
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _CrtSetBreakAlloc(NUM);	//allocation number ex {123} etc shown in objdump as NUM
	{
	*/


	assert(sizeof(float) == 4);
	assert(sizeof(int) == 4);
	assert(sizeof(unsigned int) == 4);
	assert(sizeof(uint32_t) == 4);
	assert(sizeof(int32_t) == 4);
	assert(sizeof(uint64_t) == 8);
	assert(sizeof(int64_t) == 8);

	srand((unsigned int)time(NULL));

	CPU cpu = CPU();
	Assembler assembler = Assembler();


	//string programName = "99bottles.txt";
	//string programName = "fact.s";
	//string programName = "prime-1.txt";
	//string programName = "prime-2.s";
	string programName = "selfModifyingHelloWorld.txt";


	if(!assembler.assemble("programs/" + programName)){
		cout << "COULD NOT ASSEMBLE.  Hit enter\n";
		getchar();
		return 0;
	}

	cpu.MEM.deserialize(assembler.objectFileName);
	
	cpu.run();



	/*
	}
	_CrtDumpMemoryLeaks();
	*/
	return 0;
}
