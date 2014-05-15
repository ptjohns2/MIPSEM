#ifndef __DISASSEMBLER_HPP__
#define __DISASSEMBLER_HPP__

#include "Instruction.hpp"
#include "InstructionDataBank.hpp"
#include "BitResolver.hpp"
#include "StringResolver.hpp"
#include "mnemonics.hpp"

class Decoder{
	public:
		Decoder();
		Decoder(InstructionDataBank* bank);
		~Decoder();

		Instruction* decode(instr i);
		
		static string extractBitrange(string value, bitRange range);
		static string extractBitrange(string value, unsigned int start, unsigned int end);


	private:
		
		BitResolver resolver;
		string decodeArgument(string binStr, string parameter);



};










#endif