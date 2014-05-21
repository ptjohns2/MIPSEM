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
		string decodeArgumentToMnemonic(string binStr, string parameter);
		int64_t decodeArgumentToValue(string binStr, string parameter);
		string decodeInstruction(string binStr, string name, vector<string> parameters);
		string decodeAbnormalInstruction(string binStr, string name, vector<string> parameters, int id, vector<int64_t> &argumentValues);

		//Members
		BitResolver resolver;


};










#endif