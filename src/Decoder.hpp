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
		Instruction buildInstruction(instr i);
		Instruction buildInstruction(string binStr);
		
		static string extractBitrange(string value, bitrange range);
		static string extractBitrange(string value, unsigned int start, unsigned int end);

	private:
		//Methods
		string decodeArgument(string binStr, string parameter);
		string decodeInstruction(string binStr, string instruction);
		string decodeAbnormalInstruction(string binStr, string instruction);

		//Members
		BitResolver resolver;


};










#endif