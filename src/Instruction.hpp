#ifndef __INSTRUCTION_HPP__
#define __INSTRUCTION_HPP__

#include "InstructionData.hpp"
#include "types.hpp"

#include <string>

using namespace std;

class Instruction{
	public:
		//Methods
		Instruction();
		Instruction(InstructionData* instructionData, string asmString, instr bin, int32_t arguments[NUMBER_OF_PARAMETERS]);
		~Instruction();

		InstructionData* getInstructionData() const;
		string getAsmString() const;
		instr getBin() const;
		int32_t getArgumentValue(int) const;

	private:
		//Members
		InstructionData* instructionData;
		string asmString;
		instr bin;
		int32_t arguments[NUMBER_OF_PARAMETERS];
		

	private:





};













#endif