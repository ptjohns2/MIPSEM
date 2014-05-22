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

		static int decodeArgumentToValue(string binStr, string parameter);
		static string decodeAbnormalInstruction(string binStr, string name, vector<string> parameters, int id, vector<int> &argumentValues);

	private:
		//Methods
		static string decodeArgumentToMnemonic(string binStr, string parameter);
		static string decodeInstruction(string binStr, string name, vector<string> parameters);

		//Members
		BitResolver resolver;


};










#endif