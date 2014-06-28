

#include "InstructionDataBank.hpp"
#include "CPU.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"
#include "parse.hpp"
#include "VirtualMemory.hpp"

#include <bitset>
#include <cassert>
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
	
	InstructionDataBank bank = InstructionDataBank();
	bank.loadFile("instructions.txt");
	Encoder e = Encoder(&bank);
	Decoder d = Decoder(&bank);
	BitResolver br = BitResolver(&bank);
	StringResolver sr = StringResolver(&bank);
	CPU cpu = CPU();

	
	VirtualMemory vm = VirtualMemory(&d);
	


	
	int sfdjsdkfdsdfsds = 4;
	

	
	vector<pair<virtualAddr, uint32_t>> junkValues;
	virtualAddr randVal = 1;
	for(int i=0; i<100000; i++){
		pair<virtualAddr, uint32_t> tmpPair;

		randVal += sizeof(tmpPair.first) + (rand() % 20);
		if(!(rand() % 100)){randVal += 1000;}
		
		tmpPair.first = randVal;
		tmpPair.second = rand();
		junkValues.push_back(tmpPair);
	}
	

	int dkfjasdfsdf = 1;

	for(int i=0; i<junkValues.size(); i++){
		uint32_t tmpValue = junkValues[i].second;
		vm.writeToVirtualMemorySpace(junkValues[i].first, sizeof(uint32_t), &tmpValue);
	}

	int asdkfjads = 2;
	vector<uint32_t> readValues;
	for(int i=0; i<junkValues.size(); i++){
		virtualAddr addr = junkValues[i].first;
		uint32_t* tmpValue = (uint32_t*)vm.readVirtualMemorySpaceToHeap(addr, sizeof(uint32_t));
		uint32_t readValue = *tmpValue;
		uint32_t writtenValue = junkValues[i].second;
		readValues.push_back(readValue);
		if(readValue != writtenValue){
			virtualAddr pageNum = VirtualMemoryPageTable::calculatePageNumber(addr);
			virtualAddr pageOffset = VirtualMemoryPage::calculatePageOffset(addr);
			char pipe = 200;
			cout << std::dec << i << " addr: 0x" << std::hex << addr << "\tpageNum: 0x" << std::hex << pageNum << "\tpageOffset: 0x" << std::hex << pageOffset << '\n';
			cout << pipe << "----------> written:" << std::dec << writtenValue << "\tread:" << std::dec << readValue << '\n';;
		}
		delete tmpValue;
	}


	int x = 1;
	/*
	vector<string> instrStrArr;
	instrStrArr.push_back("addi	$t0, $zero, 8");
	instrStrArr.push_back("addi	$t1, $zero, -1");
	instrStrArr.push_back("clo	$1, $t0");
	instrStrArr.push_back("clz	$2, $t0");
	instrStrArr.push_back("addi	$v0, $zero, 1");
	instrStrArr.push_back("add	$a0, $zero, $1");
	instrStrArr.push_back("syscall");

	vector<Instruction> instrArr;
	for(int i=0; i<instrStrArr.size(); i++){
		Instruction tmpInstr = e.buildInstruction(instrStrArr[i]);
		instrArr.push_back(tmpInstr);
	}

	time_t start, end;
	time(&start);
	Instruction instr = e.buildInstruction(instrStrArr[0]);
	for(int i=0; i<1; i++){
		for(int instrIndex=0; instrIndex<instrArr.size(); instrIndex++){
			cpu.executeInstruction(&instrArr[instrIndex]);
		}
	}
	time(&end);
	int timeTaken = end - start;
	*/


	return 0;
}
