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
		Instruction buildInstruction(instr ins);
		
		static int32_t extractBitrangeUnsigned(instr value, unsigned int start, unsigned int end);
		static int32_t extractBitrangeUnsigned(instr value, bitrange range);
		static int32_t extractBitrangeSigned(instr value, unsigned int start, unsigned int end);
		static int32_t extractBitrangeSigned(instr value, bitrange range);
		
		static string decodeArgumentToMnemonic(instr ins, InstructionData* id, int parameterNumber);
		static int32_t decodeArgumentToValue(instr ins, InstructionData* id, int parameterNumber);
		
		static string decodeInstruction(InstructionData* id, instr ins);
		static string decodeAbnormalInstruction(InstructionData* id, instr ins, int32_t argumentValues[NUMBER_OF_PARAMETERS]);


	private:		
		BitResolver resolver;


};










#endif