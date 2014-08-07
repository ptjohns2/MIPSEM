#include "BitManip.hpp"

#include "types.hpp"

#include <iostream>

using namespace std;

inline int32_t signExtendWord(uint32_t val, size_t size){
	uint32_t extendableBits = SIZE_BITS_WORD - (SIZE_BITS_BYTE * size);
	int32_t signedVal = (int32_t)val;
	signedVal <<= extendableBits;
	signedVal >>= extendableBits;
	return signedVal;
}




