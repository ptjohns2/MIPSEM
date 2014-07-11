#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include "Decoder.hpp"
#include "Instruction.hpp"
#include "InstructionDataBank.hpp"
#include "StringResolver.hpp"


class Encoder{
	public:
		//Constructors
		Encoder(InstructionDataBank* bank, Decoder* decoder);
		~Encoder();

		//Methods
		Instruction buildInstruction(string asmString);
		
		static instr setBitrange(instr bin, uint32_t value, bitrange br);
		static instr setBitrange(instr bin, uint32_t value, unsigned int start, unsigned int end);

	private:
		//Methods
		instr encodeArgument(instr bin, string argument, bitrange br);
		instr encodeInstruction(InstructionData* id, vector<string> arguments);
		instr encodeAbnormalInstruction(InstructionData* id, vector<string> arguments);
		
		//Members
		StringResolver resolver;
		Decoder* decoder;
		Parser parser;

};










#endif