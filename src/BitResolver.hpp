#ifndef __BITRESOLVER_HPP__
#define __BITRESOLVER_HPP__

#include "InstructionData.hpp"
#include "InstructionDataBank.hpp"
#include "types.hpp"

#include <string>


class BitResolver{
	public:
		//Constructors
		BitResolver();
		~BitResolver();
		
		//Methods
		void addInstructionDataBank(InstructionDataBank &bank);
		InstructionData* getInstructionData(instr ins);
		

	private:
		//Methods
		static bool instrIsMatch(InstructionData* id, instr ins);

		//Members
		vector<InstructionData> table[NUMBER_OF_OPCODES];
};



#endif
