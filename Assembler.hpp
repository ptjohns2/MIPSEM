#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include "Instruction.hpp"
#include "InstructionDataBank.hpp"
#include "BitResolver.hpp"
#include "StringResolver.hpp"
#include "mnemonics.hpp"

class Assembler{
	public:
		Assembler();
		Assembler(InstructionDataBank* bank);
		~Assembler();

		Instruction* assemble(string asmString);


	private:
		//members
		StringResolver resolver;

		//methods
		int getArgumentTokenValue(string argument);
		pair<int, int> getArgumentValue(string argument);
		string encodeValueAtBitrange(string instruction, pair<bitRange, bitRange> parameter, pair<int, int> argument);
		string encodeArgument(string instruction, string parameter, string argument);


};










#endif