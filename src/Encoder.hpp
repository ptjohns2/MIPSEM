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
		Instruction* encode(string asmString);
		
		static string setBitrange(string instruction, string value, bitRange range);
		static string setBitrange(string instruction, string value, unsigned int start, unsigned int end);

	private:
		//Methods
		int getArgumentValue(string argument);
		string encodeValueAtBitrange(string instruction, bitRange parameter, int argument);
		string encodeArgument(string instruction, string parameter, string argument);
		
		//Members
		StringResolver resolver;


};










#endif