#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include "Instruction.hpp"
#include "InstructionDataBank.hpp"
#include "StringResolver.hpp"

class Encoder{
	public:
		//Constructors
		Encoder(InstructionDataBank* bank);
		~Encoder();

		//Methods
		Instruction buildInstruction(string asmString);
		
		static string setBitrange(string instruction, string value, bitrange range);
		static string setBitrange(string instruction, string value, unsigned int start, unsigned int end);

	private:
		//Methods
		static string encodeArgument(string binStr, string parameter, string argument);
		static string encodeInstruction(string binStr, vector<string> parameters, vector<string> arguments);
		static string encodeAbnormalInstruction(string binStr, vector<string> parameters, vector<string> arguments, int id);
		
		//Members
		StringResolver resolver;


};










#endif