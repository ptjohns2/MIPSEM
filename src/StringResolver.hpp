#ifndef __STRINGRESOLVER_HPP__
#define __STRINGRESOLVER_HPP__

#include "InstructionData.hpp"
#include "types.hpp"
#include "InstructionDataBank.hpp"

#include <string>
#include <vector>


class StringResolver{
	public:
		//Constructors
		StringResolver(InstructionDataBank* bank);
		~StringResolver();

		//Methods
		void addInstructionDataBank(InstructionDataBank* bank);
		InstructionData* getInstructionData(string instructionString);

	private:
		//Methods
		void addInstructionData(InstructionData* id);
		bool instructionStrIsMatch(InstructionData* id, string rightInstrStr);

		int hash(string);	
		static string hashInstructionString(string instructionString);
		static string hashInstructionTokens(string name, vector<string> arguments);


		//Members
		std::hash<string> hasher;
		vector<InstructionData*> table[INSTRUCTION_DATA_HASH_TABLE_SIZE];
};



#endif
