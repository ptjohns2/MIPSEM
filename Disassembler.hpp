#ifndef __DISASSEMBLER_HPP__
#define __DISASSEMBLER_HPP__

#include "Instruction.hpp"
#include "InstructionDataBank.hpp"
#include "BitResolver.hpp"
#include "StringResolver.hpp"
#include "mnemonics.hpp"

class Disassembler{
	public:
		Disassembler();
		Disassembler(InstructionDataBank* bank);
		~Disassembler();

		Instruction* disassemble(instr i);


	private:
		BitResolver resolver;
		string decodeArgument(string binStr, string parameter);



};










#endif