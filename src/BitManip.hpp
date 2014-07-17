#ifndef __BITMANIP_HPP__
#define __BITMANIP_HPP__

#include "types.hpp"

#include <cassert>
#include <stdint.h>
#include <string.h> // memcpy

extern inline int32_t signExtend(uint32_t, size_t);

extern void printbin(const void* p, int len);


//===============Template functions:

template<typename datatype> 
datatype readMemAs(void* ptr){
	datatype x = 0;
	memcpy(&x, ptr, sizeof(datatype));
	return x;
}
template int8_t		readMemAs<int8_t>	(void* ptr);
template uint8_t	readMemAs<uint8_t>	(void* ptr);
template int16_t	readMemAs<int16_t>	(void* ptr);
template uint16_t	readMemAs<uint16_t>	(void* ptr);
template int32_t	readMemAs<int32_t>	(void* ptr);
template uint32_t	readMemAs<uint32_t>	(void* ptr);
template instr		readMemAs<instr>	(void* ptr);
template int64_t	readMemAs<int64_t>	(void* ptr);
template uint64_t	readMemAs<uint64_t>	(void* ptr);
template float		readMemAs<float>	(void* ptr);
template double		readMemAs<double>	(void* ptr);



template<typename datatype>
void writeMemAs(void* ptr, datatype value){
	memcpy(ptr, &value, sizeof(value));
}
template void		writeMemAs<int8_t>	(void* ptr, int8_t value);
template void		writeMemAs<uint8_t>	(void* ptr, uint8_t value);
template void		writeMemAs<int16_t>	(void* ptr, int16_t value);
template void		writeMemAs<uint16_t>(void* ptr, uint16_t value);
template void		writeMemAs<int32_t>	(void* ptr, int32_t value);
template void		writeMemAs<uint32_t>(void* ptr, uint32_t value);
template void		writeMemAs<int64_t>	(void* ptr, int64_t value);
template void		writeMemAs<uint64_t>(void* ptr, uint64_t value);
template void		writeMemAs<float>	(void* ptr, float value);
template void		writeMemAs<double>	(void* ptr, double value);



template<typename part, typename whole> 
whole concatenateBitPair(part msb, part lsb){
	assert((2 * sizeof(part)) == sizeof(whole));
	part tmpArr[2] = {msb, lsb};
	whole retVal = readMemAs<whole>(&tmpArr[0]);
	return retVal;
}
template uint16_t	concatenateBitPair<uint8_t, uint16_t>	(uint8_t msb, uint8_t lsb);
template uint32_t	concatenateBitPair<uint16_t, uint32_t>	(uint16_t msb, uint16_t lsb);
template uint64_t	concatenateBitPair<uint32_t, uint64_t>	(uint32_t msb, uint32_t lsb);
template double		concatenateBitPair<float, double>		(float msb, float lsb);



template<typename part, typename whole> 
part splitToUpperHalf(whole val){
	// [__msb 0__][lsb 1]
	assert((2 * sizeof(part)) == sizeof(whole));
	part tmpArr[2] = {0, 0};
	memcpy(&tmpArr[0], &val, sizeof(whole));
	return tmpArr[0];
}
template uint32_t	splitToUpperHalf<uint32_t, uint64_t>(uint64_t val);
template float		splitToUpperHalf<float, double>		(double val);



template<typename part, typename whole> 
part splitToLowerHalf(whole val){
	// [msb 0][__lsb 1__]
	assert((2 * sizeof(part)) == sizeof(whole));
	part tmpArr[2] = {0, 0};
	memcpy(&tmpArr[0], &val, sizeof(whole));
	return tmpArr[1];
}
template uint32_t	splitToLowerHalf<uint32_t, uint64_t>(uint64_t val);
template float		splitToLowerHalf<float, double>		(double val);


















#endif