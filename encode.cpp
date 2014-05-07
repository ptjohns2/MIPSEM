
#include <bitset>
#include <cassert>

#include "encode.hpp"
#include "decode.hpp"
#include "types.hpp"
#include "Instruction.hpp"
#include "stringManip.hpp"


string encode::setBitrange(string instruction, string value, bitRange range){
	return setBitrange(instruction, value, range.first, range.second);
}

string encode::setBitrange(string instruction, string value, unsigned int start, unsigned int end){
	assert(instruction.length() == INSTRUCTIONSIZE);
	
	int segmentSize = start - end + 1;
	assert(segmentSize <= value.length());

	int instructionStart = instruction.length() - start - 1;
	int valueStart = value.length() - segmentSize;

	for(int i=0; i<segmentSize; i++){
		instruction[instructionStart + i] = value[valueStart + i];
	}

	return instruction;
}











