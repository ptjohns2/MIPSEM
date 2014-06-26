

#include "InstructionDataBank.hpp"
#include "CPU.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"
#include "parse.hpp"

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


	return 0;
}
