#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include "Instruction.hpp"
#include "InstructionDataBank.hpp"
#include "BitResolver.hpp"
#include "StringResolver.hpp"
#include "mnemonics.hpp"

class Encoder{
	public:
		Encoder();
		Encoder(InstructionDataBank* bank);
		~Encoder();

		Instruction* encode(string asmString);
		
		static string setBitrange(string instruction, string value, bitRange range);
		static string setBitrange(string instruction, string value, unsigned int start, unsigned int end);

	private:
		//members
		StringResolver resolver;

		//methods
		int getArgumentValue(string argument);
		string encodeValueAtBitrange(string instruction, bitRange parameter, int argument);
		string encodeArgument(string instruction, string parameter, string argument);


};










#endif