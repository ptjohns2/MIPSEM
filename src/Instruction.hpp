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
		Instruction(InstructionData*, string, string, instr, vector<int64_t>);
		~Instruction();

		InstructionData* getId();
		string getAsmString();
		string getBinString();
		instr getBin();
		vector<int64_t> getArguments();

	private:
		//Members
		InstructionData* id;
		string asmString;
		string binString;
		instr bin;
		vector<int64_t> arguments;


	private:





};













#endif