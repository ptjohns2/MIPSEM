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
		~Instruction();

		void execute();

		//Members
		InstructionData* id;
		string asmString;
		string binString;
		instr bin;


	private:





};













#endif