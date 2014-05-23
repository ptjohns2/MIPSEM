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

		InstructionData* getId() const;
		string getAsmString() const;
		string getBinString() const;
		instr getBin() const;
		vector<int> getArguments() const;

	private:
		//Members
		InstructionData* id;
		string asmString;
		string binString;
		instr bin;
		vector<int> arguments;
		

	private:





};













#endif