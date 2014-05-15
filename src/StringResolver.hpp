#ifndef __STRINGRESOLVER_HPP__
#define __STRINGRESOLVER_HPP__

#include "types.hpp"
#include <string>
#include <vector>
#include "InstructionData.hpp"
#include "InstructionDataBank.hpp"


class StringResolver{
	public:
		//Methods
		StringResolver();
		StringResolver(InstructionDataBank* bank);
		~StringResolver();

		void addInstructionData(InstructionData* id);
		void addInstructionDataBank(InstructionDataBank* bank);
		InstructionData* getInstructionData(string instructionString);
		static string instructionStringToHashableString(string instructionString);


		//Members


	private:
		//Methods
		int hash(string);	

		//Members
		std::hash<std::string> hasher;
		vector<InstructionData*> table[INSTRUCTION_DATA_HASH_TABLE_SIZE];
		int num;


};



#endif
