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
		Instruction(InstructionData*, string, string, instr, vector<int>);
		~Instruction();

		InstructionData* getInstructionData() const;
		string getAsmString() const;
		string getBinString() const;
		instr getBin() const;
		uint32_t getArgumentValue(int) const;

	private:
		//Members
		InstructionData* instructionData;
		string asmString;
		string binString;
		instr bin;
		uint32_t arguments[NUMBER_OF_ARGUMENTS];
		

	private:





};













#endif