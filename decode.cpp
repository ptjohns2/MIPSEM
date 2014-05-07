#include "decode.hpp"
#include <iostream>
#include <bitset>
#include "stringManip.hpp"

//TODO: check signs


string decode::extractBitrange(string value, bitRange range){
	return extractBitrange(value, range.first, range.second);
}

string decode::extractBitrange(string value, unsigned int start, unsigned int end){
	int valueStart = value.length() - start - 1;
	int segmentSize = start - end + 1;
	string retVal = value.substr(valueStart, segmentSize);
	return retVal;
}


