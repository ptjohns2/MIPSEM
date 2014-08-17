#ifndef __ENCODER_HPP__
#define __ENCODER_HPP__

#include "Decoder.hpp"
#include "Instruction.hpp"
#include "InstructionDataBank.hpp"
#include "StringResolver.hpp"


class Encoder{
	public:
		//Constructors
		Encoder();
		~Encoder();

		//Methods
		Instruction buildInstruction(string asmString);
		
		static instr setBitrange(instr bin, uint32_t value, bitrange br);
		static instr setBitrange(instr bin, uint32_t value, unsigned int start, unsigned int end);

		//Members
		StringResolver resolver;

	private:
		//Methods
		instr encodeArgument(instr bin, string argument, bitrange br);
		instr encodeInstruction(InstructionData* id, vector<string> arguments);
		instr encodeAbnormalInstruction(InstructionData* id, vector<string> arguments);
		
		//Members
		Decoder decoder;
		Parser parser;

};










#endif