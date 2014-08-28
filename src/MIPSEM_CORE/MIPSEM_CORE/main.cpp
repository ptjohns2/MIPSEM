#define _CRTDBG_MAPALLOC
#include <stdlib.h>
#include <crtdbg.h>



#include "Assembler.hpp"
#include "BitManip.hpp"
#include "Core.hpp"
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

int main(int argc, char** args){
//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); _CrtSetBreakAlloc(NUM);{	//allocation number ex {123} etc shown in objdump as NUM
	
	assert(sizeof(float) == 4);
	assert(sizeof(int) == 4);
	assert(sizeof(unsigned int) == 4);
	assert(sizeof(uint32_t) == 4);
	assert(sizeof(int32_t) == 4);
	assert(sizeof(uint64_t) == 8);
	assert(sizeof(int64_t) == 8);
	srand((unsigned int)time(NULL));

	if(!argc == 2){
		cout << "Error: invalid number of arguments.  Only one can be used, *.MIPSEMobj file to run";
		return 0;
	}
	string fileName(args[1]);
	if(Parser::isNestedByQuotes(fileName)){
		fileName = Parser::removeNestedQuotes(fileName);
	}
	if(Parser::filePathToParentDirectory(fileName).empty()){
		//add later
	}
	ifstream file(fileName.c_str());
	if(!file.good()){
		cout << "Unable to open object file \"" << fileName << "\".";
		getchar();
		return 0;
	}

	
	Core core;
	core.MEM.deserialize(fileName);
	core.run();



//	} _CrtDumpMemoryLeaks();

	
	return 0;
}

