#ifndef __ENCODE_HPP__
#define __ENCODE_HPP__

#include "types.hpp"
#include "Instruction.hpp"


class encode{
	public:
		static string setBitrange(string instruction, string value, bitRange range);
		static string setBitrange(string instruction, string value, unsigned int start, unsigned int end);




};






#endif