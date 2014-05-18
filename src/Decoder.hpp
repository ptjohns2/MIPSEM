#ifndef __DISASSEMBLER_HPP__
#define __DISASSEMBLER_HPP__

#include "BitResolver.hpp"
#include "Instruction.hpp"
#include "InstructionDataBank.hpp"

class Decoder{
	public:
		//Constructors
		Decoder(InstructionDataBank* bank);
		~Decoder();
		
		//Methods
		Instruction* decode(instr i);
		
		static string extractBitrange(string value, bitRange range);
		static string extractBitrange(string value, unsigned int start, unsigned int end);


	private:
		//Methods
		string decodeArgument(string binStr, string parameter);
		
		//Members
		BitResolver resolver;


};










#endif