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
		string encodeArgument(string binStr, string parameter, string argument);
		string encodeInstruction(string binStr, vector<string> parameters, vector<string> arguments);
		string encodeAbnormalInstruction(string binStr, vector<string> parameter, vector<string> argument);
		
		//Members
		StringResolver resolver;


};










#endif